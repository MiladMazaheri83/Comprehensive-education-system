#include "TA_formPost.hpp"

TA_formPost::TA_formPost(int postId, string userId, string message, string imagePath, int courseId)
    : Post(postId, userId, message, imagePath), courseId(courseId) {}

TA_formPost::~TA_formPost() {}