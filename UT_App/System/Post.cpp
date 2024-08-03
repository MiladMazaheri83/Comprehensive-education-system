#include "Post.hpp"

Post::Post(int postId, string userId, string message, string imagePath) : postId(postId), userId(userId), message(message), imagePath(imagePath) {}

Post::~Post() {}