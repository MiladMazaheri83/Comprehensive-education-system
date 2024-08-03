#ifndef TA_FORM_HPP
#define TA_FORM_HPP

#include "Post.hpp"

class TA_formPost : public Post
{
public:
    int courseId;
    TA_formPost(int postId,string userId, string message, string imagePath, int courseId);
    ~TA_formPost();
};

#endif // TA_FORM_HPP