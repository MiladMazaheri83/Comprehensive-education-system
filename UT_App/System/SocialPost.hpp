#ifndef SOCIALPOST_HPP
#define SOCIALPOST_HPP

#include "Post.hpp"

class SocialPost : public Post
{
public:
    string title;
    SocialPost(int postId, string userId, string message, string imagePath, string title);
    ~SocialPost();
};

#endif // SOCIALPOST_HPP