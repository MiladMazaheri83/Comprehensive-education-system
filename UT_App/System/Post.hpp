#ifndef POST_HPP
#define POST_HPP

#include <string>
#include <vector>
#include <list>
#include <map>
#include <variant>
using namespace std;

class Post
{
private:
    int postId;

public:
    string userId;
    string message;
    string imagePath;
    Post(int postId,string userId, string message, string imagePath);
    virtual ~Post();
    int getPostId() { return postId; };
};

#endif // POST_HPP