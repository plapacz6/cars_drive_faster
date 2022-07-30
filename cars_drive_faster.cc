/*
author: plapacz6@gmail.com
data: 2022-07-22
ver: 0.1.0
*/
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

#include <time.h>  //clock_nanosleep()
#include <unistd.h>

#include <thread>
// #include <chrono>  
// #include <mutex>

using namespace std;
using namespace cv;
namespace cars__higher_speed {  
/* ----------------------------------------- */
// chrono::milliseconds game_frame_time(33);
// mutex::mutex mtx_speed_car1;
// mutex::mutex mtx_v_shift_unit;
// mutex::mutex mtx_get_timmer;
//this_thread::sleep_for(game_frame_time);

/* ----------------------------------------- */
class road_t;
class car1_t;
class car2_t;
class hole_t;
class bush_t;
class obstacle_t;
/* ----------------------------------------- */
struct game_mutex_t {
  pthread_mutex_t lock_get_time;
  pthread_mutexattr_t mutex_attr_get_time;  
  
  pthread_mutex_t lock_speed_car1;
  pthread_mutexattr_t mutex_attr_speed_car1;  

  pthread_mutex_t lock_v_shift_unit;
  pthread_mutexattr_t mutex_attr_v_shift_unit;    
} mtx;

/* ----------------------------------------- */

#define PDEBUG_(X) cout << #X << " " << X << endl;

/* ----------------------------------------- */

void init_mutex(){

  int ret;
  ret = pthread_mutex_init(&mtx.lock_speed_car1, &mtx.mutex_attr_speed_car1);
  if(ret){
    cerr << "mutex init" << endl;
    exit(1);
  }
  
  ret = pthread_mutex_init(&mtx.lock_get_time, &mtx.mutex_attr_get_time);
  if(ret){
    cerr << "mutex init" << endl;
    exit(1);
  }

  ret = pthread_mutex_init(&mtx.lock_v_shift_unit, &mtx.mutex_attr_v_shift_unit);
  if(ret){
    cerr << "mutex init" << endl;
    exit(1);
  }
}

void destroy_mutex(){
  pthread_mutex_destroy(&mtx.lock_speed_car1);
  pthread_mutex_destroy(&mtx.lock_get_time);
  pthread_mutex_destroy(&mtx.lock_v_shift_unit);
}

void get_time(timespec *ptr_now, long ns){
pthread_mutex_lock(&mtx.lock_get_time);
    int ret = clock_gettime(CLOCK_MONOTONIC, ptr_now);
    if(ret){
      cerr << "game_control(), clock_gettime()" << endl;
      exit(1);
    }
    ptr_now->tv_nsec += ns;
    if(ptr_now->tv_nsec > 1000000000L) {
      ptr_now->tv_nsec -= 1000000000L;
      ptr_now->tv_sec++;
    } 
    pthread_mutex_unlock(&mtx.lock_get_time);
}

/* ----------------------------------------- */


void paste_img(const Mat& src, const Rect& coord, Mat& dst){
  for(int w = 0; w < src.rows && w < coord.height; ++w){
    for(int c = 0; c < src.cols && c < coord.width; ++c){
      dst.at<Vec3b>(coord.y + w, coord.x + c) = src.at<Vec3b>(w, c);
    }
  }
}

/**
 * @brief pasting a part of the image that may protrude vertically
 * beyond the dimensions of the dst
 * 
 * @param src 
 * @param coord 
 * @param dst 
 */
void paste_img_vert_partialy(const Mat& src, const Rect& coord, Mat& dst){
  for(int w = 0; 
      w < src.rows && w < coord.height;
      ++w){
    for(int c = 0; c < src.cols && c < coord.width; ++c){
      if(coord.y + w < dst.rows && coord.y + w > 0){
        dst.at<Vec3b>(coord.y + w, coord.x + c) = src.at<Vec3b>(w, c);
      }
    }
  }
}

/**
 * @brief paste img to borad in vertical wrap mode
 * 
 */
void paste_img_vert_wrap(const Mat& src, const Rect& coord, int vert_shift, Mat& dst){
  
  //PDEBUG_(vert_shift);
  // while(vert_shift >= 500) {
  //   vert_shift -= 500;
  while(vert_shift >= coord.height) {
    vert_shift -= coord.height;    
  }
  int w1 = 0; 
  for(int w2 = vert_shift;
      w1 < src.rows - vert_shift && w2 < coord.height; 
      ++w1, ++w2)
    {
    for(int c = 0; c < src.cols && c < coord.width; ++c){
      dst.at<Vec3b>(coord.y + w2, coord.x + c) = src.at<Vec3b>(w1, c);
    }
  }  
  for(int w2 = 0; 
      w1 < src.rows && w2 < vert_shift;
      ++w1, ++w2)
    {        
    for(int c = 0; c < src.cols && c < coord.width; ++c){
      dst.at<Vec3b>(coord.y + w2, coord.x + c) = src.at<Vec3b>(w1, c);
    }
  }
}


void paste_img_horiz_wrap(const Mat& src, const Rect& coord, int horiz_shift, Mat& dst){
  while(horiz_shift >= coord.width){
    horiz_shift -= coord.width;
  }
  int c1 = 0;
  for(int w = 0; w < src.rows && w < dst.rows; ++w){
    c1 = 0;
    for(int c2 = horiz_shift;
        c1 < src.cols - horiz_shift && c2 < coord.width;
        ++c1, ++c2)
    {
      dst.at<Vec3b>(coord.y + w, coord.x + c2) = src.at<Vec3b>(w, c1);
    }    
    for(int c2 = 0;
        c1 < src.cols - horiz_shift && c2 < coord.width;
        ++c1, ++c2)        
    {
      dst.at<Vec3b>(coord.y + w, coord.x + c2) = src.at<Vec3b>(w, c1);
    }
  }
}

/* ----------------------------------------- */

enum lang_t {
  ENG = 0, PL = 1
} lang;
const int lang_amount = 2;
const int messages_amount = 1;
string messages[lang_amount][messages_amount] { 
  //ENG
  {
  "esc      - end\n<-  ->   - control car",
  },
  //PL
  {
  "esc      - koniec\n<-  ->   - sterowanie samochodem",
  },  
};

void print_message(int nr){
  cout << messages[lang][nr] << endl;
}
/* ----------------------------------------- */

class game_images_t {
  public:
  
  Mat img_roadside;
  Mat img_lane;
  Mat img_car1;
  Mat img_car2;
  Mat img_hole;
  Mat img_bush;
  Mat img_lane_dotted;
  
    
  game_images_t(){
    load_images();
  }
  void load_images();

} game_images;

void game_images_t::load_images(){
  try{
    img_roadside = imread("roadside.jpg");
    img_lane = imread("lane.jpg");
    img_car1 = imread("car1.jpg");
    img_car2 = imread("car2.jpg");
    img_hole = imread("hole.jpg");
    img_bush = imread("bush.png");
    img_lane_dotted = imread("line_dotted.jpg");
    if(img_roadside.empty() 
      || img_lane.empty()
      || img_car1.empty()
      || img_car2.empty()
      || img_hole.empty()
      || img_bush.empty()
    ){
      throw;
    }
  }
  catch(...){
    cerr << "road_t - exception" << endl;
    exit(EXIT_FAILURE);
  }
}

/* ----------------------------------------- */


enum lane_t {   //for road_t::def_rect()
  IDX_LANE_L = 0,
  IDX_LANE_M = 1,
  IDX_LANE_R = 2
};

enum pos_t {  
  LANE_L = 0,
  LANE_M = 1,
  LANE_R = 2,
  ROADSIDE_L = 3,
  ROADSIDE_R = 4,
  POS_NOT_EXISTING = 5
};


struct board_def_t {
  int roadside_width;
  int lane_width;
  int road_hight;  //length of the visible part of road
  const string& wndName;
  long time_period_ns;
  time_t time_period_s;
  long time_speed_up_ns;
  time_t time_speed_up_s;
  double begining_speed_car1;
  double step_speed_up;
  double max_speed;

  Rect calc_begin_rect_lane(Mat &img, int lane);
  Rect calc_begin_rect_roadside(Mat &img, int place);
} b_df = {
    200,
    75,
    500,
    "cars - higher speed",
    33000000,  //ms
    0,
    1000000000,
    0,
    0.1,
    0.4,
    35.0
  };

Rect board_def_t::calc_begin_rect_lane(Mat &img, int lane){
  return Rect(
    roadside_width + lane_width * lane + 
      (lane_width - img.cols) / 2,
    0, 
    img.cols ,    
    img.rows
  );
}

Rect board_def_t::calc_begin_rect_roadside(Mat &img, int place){
  int roadside;
  int lane;
  if(place == ROADSIDE_L){
    roadside = 0;
    lane = 0;
  }
  if(place == ROADSIDE_R){
    roadside = 1;
    lane = 3;
  }
  return Rect(
    roadside_width * roadside + lane_width * lane + 
      (roadside_width - img.cols) / 2,
    0, 
    img.cols ,    
    img.rows
  );
}

/* ----------------------------------------- */

class game_state_t {
  public:
    bool hole_processed;
    bool car2_processed;
    bool bush_processed;
} game_state;

/* ----------------------------------------- */

class speed_car1_t {
  private:
  double speed_car1;
  public:
  speed_car1_t(){
    pthread_mutex_lock(&mtx.lock_speed_car1);
    speed_car1 = b_df.begining_speed_car1;
    pthread_mutex_unlock(&mtx.lock_speed_car1);
  }
  inline double get(){
    double spped_car1_;
    pthread_mutex_lock(&mtx.lock_speed_car1);
    spped_car1_ = speed_car1;
    pthread_mutex_unlock(&mtx.lock_speed_car1);
    return spped_car1_;
  }
  inline void set(double&& speed_car1_){
    pthread_mutex_lock(&mtx.lock_speed_car1);
    speed_car1 = speed_car1_;
    pthread_mutex_unlock(&mtx.lock_speed_car1);
  }
} speed_car1;

  class v_shift_unit_t {
    int v_shift_unit;  //<< unit shift calculated based on car1 speed, and prev coord_shift
    public:
    v_shift_unit_t(){       
      pthread_mutex_lock(&mtx.lock_speed_car1);
      pthread_mutex_lock(&mtx.lock_v_shift_unit);
      v_shift_unit = 0;
      pthread_mutex_unlock(&mtx.lock_v_shift_unit);
      pthread_mutex_unlock(&mtx.lock_speed_car1);
    };
    inline int get(){ 
      int v_shift_unit_;
      //cout << "v_shift_u.get() " << endl;
      pthread_mutex_lock(&mtx.lock_speed_car1);
      pthread_mutex_lock(&mtx.lock_v_shift_unit);
      v_shift_unit_ =  v_shift_unit;
      pthread_mutex_unlock(&mtx.lock_v_shift_unit);
      pthread_mutex_unlock(&mtx.lock_speed_car1);
      return v_shift_unit_;
    }
    inline void set(int v_shift_unit_){
      //cout << "v_shift_u.set() " << endl;
      pthread_mutex_lock(&mtx.lock_speed_car1);
      pthread_mutex_lock(&mtx.lock_v_shift_unit);
      v_shift_unit = v_shift_unit_;
      pthread_mutex_unlock(&mtx.lock_v_shift_unit);
      pthread_mutex_unlock(&mtx.lock_speed_car1);
    }    
  } v_shift_unit;

bool game_break = false;
road_t *ptr_road = NULL;
car1_t *ptr_car1 = NULL;

/* ----------------------------------------- */


/**
 * @brief game board
 * 
 */
class board_t {
  public:
  board_t();
  //~board_t()
  void show();
  void load_images();

  Mat b;  

} board;

board_t::board_t(){
  b = Mat(
      b_df.road_hight,
      b_df.roadside_width * 2 + b_df.lane_width * 3,
      CV_8UC3
    );
}
void board_t:: show(){
  imshow(b_df.wndName, b);
}

/* ----------------------------------------- */

class obstacle_t {
  public:
  Rect coord;         //< current coordinates
  virtual void action() = 0;  
};

/* ----------------------------------------- */

enum road_line_type_t {
  LINE_DOTTED
};

class road_line_t {
  
  public:      
  road_line_t(pos_t lane_on_left, road_line_type_t type_);
  //~road_line_t();
  void set_img(road_line_type_t type_);
  
  Rect coord; //< absolute lane position on road  
  Mat* ptr_img = NULL; //< line image depending on line type

  road_line_type_t type;
};

/**
 * @brief Construct a new road line t::road line t object
 * 
 * @param lane_on_left //< (LANE_L, LANE_M)
 */
road_line_t::road_line_t(pos_t lane_on_left, road_line_type_t type_){  
  CV_Assert(lane_on_left < 3 && lane_on_left >= 0);

  int line_half_width;
  type = type_; 
  set_img(type_);
  line_half_width = ptr_img->cols / 2;
     
  coord = Rect(    
    b_df.roadside_width + (
      lane_on_left == LANE_L
      ? b_df.lane_width * 1 //static_cast<int>(lane_on_left) - 
      : b_df.lane_width * 2 //static_cast<int>(lane_on_left) -     
      ) - line_half_width,    
    0,  //y, row0
    ptr_img->cols, //width
    ptr_img->rows  //hight
  );  
}

void road_line_t::set_img(road_line_type_t type_){
  type = type_;
  //if(type == LINE_DOTTED)
    ptr_img = &game_images.img_lane_dotted;  
}

/* ----------------------------------------- */

class road_t {

  public:

  int v_shift_total; //total shift
  
  road_t();
  //~road_t();
  void calculate_shift();
  void draw();
  
  road_line_t line1;
  road_line_t line2;

  Rect roadside_L;
  Rect lane_L;
  Rect lane_M;
  Rect lane_R;
  Rect roadside_R;

  Rect car1_L;
  Rect car1_M;
  Rect car1_R;
      
  Mat empty_road;
  Mat img_roadside; 

  vector<obstacle_t> road_objects;
};
//road_t* ptr_road = NULL;
road_t::road_t()
  : line1(LANE_L, LINE_DOTTED), line2(LANE_R, LINE_DOTTED)
{
  empty_road = Mat::zeros(
    Size(
      b_df.roadside_width * 2 + b_df.lane_width * 3,
      b_df.road_hight),
    CV_8UC3
  );
  
  roadside_L = Rect(
    0,
    0, 
    b_df.roadside_width,
    b_df.road_hight);
  lane_L = Rect(
    b_df.roadside_width + b_df.lane_width * 0,
    0, 
    b_df.roadside_width + b_df.lane_width * 1,
    b_df.road_hight);
  lane_M = Rect(
    b_df.roadside_width + b_df.lane_width * 1,
    0, 
    b_df.roadside_width + b_df.lane_width * 2,
    b_df.road_hight);
  lane_R = Rect(
    b_df.roadside_width + b_df.lane_width * 2,
    0, 
    b_df.roadside_width + b_df.lane_width * 3,
    b_df.road_hight);
  roadside_R = Rect(
    b_df.roadside_width + b_df.lane_width * 3,
    0, 
    b_df.roadside_width * 2 + b_df.lane_width * 3,
    b_df.road_hight);    
  
  if(game_images.img_car1.empty()){
    throw;  //game_images.load_images() must be call before
  } 
  car1_L = Rect {
    b_df.roadside_width + b_df.lane_width * 0 + 
      (b_df.lane_width - game_images.img_car1.cols) / 2,
    b_df.road_hight - game_images.img_car1.rows,
    game_images.img_car1.cols ,    
    game_images.img_car1.rows};
 
  car1_M = Rect {
    b_df.roadside_width + b_df.lane_width * 1 + 
      (b_df.lane_width - game_images.img_car1.cols) / 2,
    b_df.road_hight - game_images.img_car1.rows,
    game_images.img_car1.cols ,    
    game_images.img_car1.rows};
 
  car1_R = Rect {
    b_df.roadside_width + b_df.lane_width * 2 + 
      (b_df.lane_width - game_images.img_car1.cols) / 2,
    b_df.road_hight - game_images.img_car1.rows,
    game_images.img_car1.cols ,    
    game_images.img_car1.rows};  

  paste_img(game_images.img_roadside, roadside_L, empty_road);  
  paste_img(game_images.img_lane, lane_L, empty_road);
  paste_img(game_images.img_lane, lane_M, empty_road);
  paste_img(game_images.img_lane, lane_R, empty_road);
  paste_img(game_images.img_roadside, roadside_R, empty_road);  
}

void road_t::calculate_shift(){ 
  cout << "calc_shift() " << endl;
  double curr_speed = speed_car1.get();
  v_shift_unit.set( static_cast<int>(       //50px == 2cm = 0,02m ->   0.01m == 25px == 1m real
    (curr_speed ) *                      //10 == 4km/h == 1.1m/s
    (b_df.time_period_ns ) / 26500000)   //33000000ns == 0,033s      
  );                                       //--------------------------
                                          //0.033s -> 0.3m/s -> 25px/3 = 8.33 px  
  //PDEBUG_(v_shift_unit.get());
}

void road_t:: draw(){    
  int v_shift_unit_get = v_shift_unit.get();
  pthread_mutex_lock(&mtx.lock_speed_car1);
  board.b = empty_road.clone();  
  
  v_shift_total += v_shift_unit_get;
  if(v_shift_total >  b_df.road_hight){
    v_shift_total = v_shift_total - b_df.road_hight;
  }
  
  paste_img_vert_wrap(*(line1.ptr_img), line1.coord, v_shift_total,  board.b);
  paste_img_vert_wrap(*(line2.ptr_img), line2.coord, v_shift_total,  board.b);
  
  pthread_mutex_unlock(&mtx.lock_speed_car1);
  // PDEBUG_( game_images.img_car1.size() );
  // PDEBUG_( car1_L );
  // PDEBUG_( board.b.size() );      
}  

/* ----------------------------------------- */

class bush_t : public obstacle_t {
  public:  
  bush_t(pos_t pos_begin_, pos_t target_);
  //~bush_t();  
  void action();
  
  Rect coord_targed;  //< target coordinates 
  //Rect coord;         //< current coordinates
};
/**
   * @brief Construct a new bush t object
   * 
   * @param pos_begin_ enum pos_t beginnin lane (ROADSIDE_L, ROADSIDE_R)
   * @param target_    enum pos_t target lane (LANE_L, LANE_M, LANE_R)
   */
bush_t::bush_t(pos_t pos_begin_, pos_t pos_target_){  
  coord = b_df.calc_begin_rect_roadside(game_images.img_bush, pos_begin_);   
  coord_targed = b_df.calc_begin_rect_lane(game_images.img_bush, pos_target_);
}    
void bush_t::action(){
  //TODO: calcualte coord according to current road speed  
  paste_img(game_images.img_bush, coord, board.b);
}

/* ----------------------------------------- */


class hole_t : public obstacle_t{
  public:  
  hole_t(pos_t pos_target_);  
  void action();
  void reset(pos_t pos_target_);

  //Rect coord;         //< current coordinates
};
/**
 * @brief Construct a new hole t::hole t object
 * 
 * @param pos_target_   enum pos_t target lane of hole (LANE_L, LANE_M, LANE_R)
 */
hole_t::hole_t(pos_t pos_target_){
  reset(pos_target_);
}
void hole_t::reset(pos_t pos_target_){
  coord = b_df.calc_begin_rect_lane(game_images.img_hole, pos_target_);
  coord.y -= game_images.img_hole.rows;
  game_state.hole_processed = true;    
}
void hole_t::action(){  
  coord.y += v_shift_unit.get();
  paste_img_vert_partialy(game_images.img_hole, coord, board.b);
  if(coord.y > b_df.road_hight){
    game_state.hole_processed = false;    
  }
}

/* ----------------------------------------- */

class car2_t : public obstacle_t{
  public:
  
  car2_t(pos_t begin_pos_, double speed);
  //~car2_t();
  void reset(pos_t begin_pos_, double speed_);
  void action();

  double speed;
  //Rect coord;         //< current coordinates
    
};
car2_t::car2_t(pos_t begin_pos_, double speed_){
  reset(begin_pos_, speed_);
}  
void car2_t::reset(pos_t begin_pos_, double speed_){
  speed = speed_;
  coord = b_df.calc_begin_rect_lane(game_images.img_car2, begin_pos_);
  coord.y -= game_images.img_car2.rows;
  game_state.car2_processed = true; 
}
void car2_t::action(){      
  coord.y += v_shift_unit.get();
  coord.y -= speed * ((b_df.time_period_ns ) / 26500000);  
  paste_img_vert_partialy(game_images.img_car2, coord, board.b);
  if(coord.y > b_df.road_hight){
    game_state.car2_processed = false;    
  }  
}
 
/* ----------------------------------------- */

/**
 * @brief players car
 * 
 */
class car1_t {
  public:
  car1_t(road_t& road_, pos_t begin_pos_, double speed_);
  //~car1_t();
  void action();

  road_t& road;  
  double speed; 
  Rect *ptr_coord;         //< current coordinates
};

/**
 * @brief Construct a new car1 t::car1 t object
 * 
 * @param road_ object road, stroing Rec of car1 position on each lane
 * @param begin_pos_ enum pos_t  beginning lane
 * @param speed_     beginning speed
 */
car1_t::car1_t(road_t& road_, pos_t begin_pos_, double speed_) 
  : road(road_)
{
  if(begin_pos_ == LANE_L)
    ptr_coord = &road_.car1_L;
  else
  if(begin_pos_ == LANE_M)
    ptr_coord = &road_.car1_M;
  else
  if(begin_pos_ == LANE_R)
    ptr_coord = &road_.car1_R;
}

void car1_t::action(){
  paste_img(game_images.img_car1, *ptr_coord, board.b);
}

/* ----------------------------------------- */

enum key_nr_t {
  KEY_ESC = 1048603,
  KEY_ESC_CAPSLOCK = 1179675,  
  KEY_LARROW = 1113937,
  KEY_RARROR = 1113939
};

/* ----------------------------------------- */

bool is_collisioin_hole(obstacle_t *ptr_obj){  
  if(             
    std::abs(ptr_obj->coord.x - ptr_car1->ptr_coord->x) < 15 &&
    (ptr_obj->coord.y + ptr_obj->coord.height) >= ptr_car1->ptr_coord->y){
    // PDEBUG_(ptr_obj->coord.x);
    // PDEBUG_(ptr_car1->ptr_coord->x);
    PDEBUG_((ptr_obj->coord.x - ptr_car1->ptr_coord->x));      
    return true;
  }
  return false;
}

bool is_collisioin_car2(obstacle_t *ptr_obj){  
  if(             
    std::abs(ptr_obj->coord.x - ptr_car1->ptr_coord->x) < 15 &&
    (ptr_obj->coord.y + ptr_obj->coord.height) >= ptr_car1->ptr_coord->y){
    // PDEBUG_(ptr_obj->coord.x);
    // PDEBUG_(ptr_car1->ptr_coord->x);
    PDEBUG_((ptr_obj->coord.x - ptr_car1->ptr_coord->x));      
    return true;
  }
  return false;
}

/* ----------------------------------------- */

pos_t draw_hole_position(){
  pos_t pos;
  if(!game_state.hole_processed){
    pos = static_cast<pos_t>(rand() % 5);
  }
  game_state.hole_processed = true;
  return pos;
}

pos_t draw_car2_position(){
    pos_t pos;
    if(!game_state.car2_processed){
      pos = static_cast<pos_t>(rand() % 3);
    }
    game_state.car2_processed = true;
    return pos;
}

/* ----------------------------------------- */
} //namespace cars__higher_speed
using namespace cars__higher_speed;

void game_control(bool *ptr_game_break){
  timespec now;
  
  lang_t lang = PL;
  key_nr_t key;  
  
  road_t& road = *ptr_road;
  car1_t my_car(road, LANE_M, 0.0);     
  ptr_car1 = &my_car;
  
  print_message(1);  
  my_car.action();
  /* EXAMPLE */

  car2_t car2(draw_car2_position(), static_cast<double>((rand()%5)+1));  
  hole_t hole2(draw_hole_position());
  
  /* EXAMPLE */
  
  while(key != KEY_ESC && key != KEY_ESC_CAPSLOCK){

    //PDEBUG_(key);    
    key = static_cast<key_nr_t>(pollKey()); 
    /* key = pollKey() == waitKeyEx(0) != waitKey(0) */
    
    for(int i = 0; i < road.road_objects.size(); i++){
      road.road_objects[i].action();
    }
    road.draw();
    if(key == KEY_LARROW){
      if(my_car.ptr_coord == &road.car1_M) /* order is important: checking M before R */
        my_car.ptr_coord = &road.car1_L;
      if(my_car.ptr_coord == &road.car1_R)
        my_car.ptr_coord = &road.car1_M;      
    }
    else
    if(key == KEY_RARROR){
      if(my_car.ptr_coord == &road.car1_M)
        my_car.ptr_coord = &road.car1_R;
      if(my_car.ptr_coord == &road.car1_L)
        my_car.ptr_coord = &road.car1_M;            
    }
    
    /* EXAMPLE */    
    hole2.action();
    car2.action();
    /* EXAMPLE */
    
    my_car.action();

    board.show();

    if(is_collisioin_hole(&hole2)){
      double speed_car_1_prev = speed_car1.get();      
      speed_car1.set(
        (speed_car_1_prev - 0.2) < 1 
        ? 1 
        : speed_car_1_prev - 0.2);      
      ptr_road->calculate_shift();
    } 
    else {
    if(is_collisioin_car2(&car2)){
      double speed_car_1_prev = speed_car1.get();      
      speed_car1.set(speed_car_1_prev * 0.9);      
      car2.coord.y -= 10;
      car2.speed += 0.2;
      ptr_road->calculate_shift();
    }
    }

    if(!game_state.hole_processed){
      hole2.reset(draw_hole_position());
    }
    if(!game_state.car2_processed){
      car2.reset(draw_car2_position(), static_cast<double>((rand()%5)+1));  
    }
    get_time(&now, b_df.time_period_ns);
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &now, NULL);
  }
  *ptr_game_break = true;
}


/**
 * @brief thread increasing car1 speed
 * 
 * @param ptr_game_break 
 */
void speed_up(bool *ptr_game_break){
  timespec now;  
  double speed_car1_get;
    
  while(!*ptr_game_break) {
    
    get_time(&now, b_df.time_speed_up_ns);
    int sleep_status = 0;
    do {
      sleep_status = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &now, NULL);
      PDEBUG_(sleep_status);
    }while(sleep_status != 0);
    speed_car1_get = speed_car1.get();
    if(speed_car1_get < b_df.max_speed +  b_df.step_speed_up){
      speed_car1.set( (speed_car1_get + b_df.step_speed_up) );
      ptr_road->calculate_shift();
    }
      
    PDEBUG_(speed_car1.get());        
    //waitKey(0);
  }
}


int main(){  
  init_mutex();
  srand(time(NULL));

  //cout << _POSIX_C_SOURCE << endl;
  namedWindow(b_df.wndName);
  road_t road;
  ptr_road = &road;
  std::thread th_game_control(game_control, &game_break);
  std::thread th_speed_up(speed_up, &game_break);

  th_game_control.join();
  th_speed_up.join();

  destroy_mutex();
  return EXIT_SUCCESS;
}



