#include "SocialPost.hpp"

SocialPost::SocialPost(int postId,string userId, string message, string imagePath, string title)
    : Post(postId, userId, message, imagePath), title(title) {}
SocialPost::~SocialPost() {}