//
//  ofxExampleTwitterClient.h
//  twitter_api
//
//  Created by Tong Wen on 2/17/14.
//
//


#pragma once


#include "ofxOAuth.h"


class ofxExampleTwitterClient: public ofxOAuth
{
public:
    ofxExampleTwitterClient()
    {
    }
    
    virtual ~ofxExampleTwitterClient()
    {
    }
    
    void setup(const std::string& consumerKey,
               const std::string& consumerSecret)
    {
        ofxOAuth::setup("https://api.twitter.com",
                        consumerKey,
                        consumerSecret);
    }
    
    // Once setup is called, authenticated calls can be made.
    // This method is just an example of whatyour calls might look like.
    std::string exampleMethod()
    {
        return get("/1.1/search/tweets.json?q=openFrameworks");
    }
    
    // This method is an example of posting an status to twitter.
    std::string exampleUpdateStatusMethod(string msg)
    {
        return post("/1.1/statuses/update.json","status="+msg);
    }
    
    std::string exampleUpdateStatusWithPhotoMethod(string msg, string imgpath)
    {
        return postfile_multipartdata("/1.1/statuses/update_with_media.json","status="+msg,"media[]",imgpath);
    }
    
};
