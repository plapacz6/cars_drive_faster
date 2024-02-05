#ifndef GAME_IMAGES_H
#define GAME_IMAGES_H

namespace csfgame {

class game_images {
    public:
    game_images();
    game_images(const  game_images&) = delete;
    virtual ~game_images() = default;
    game_images& operator=(const game_images&) = delete;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;

    protected:
    private:
};

} //namespace csfgame
#endif //GAME_IMAGES_H
