#include "reviewsreader.h"

#include <rapidjson/error/en.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/reader.h>

#include <memory>


//When there are no parsing errors, we will have an initialized array of Paper type
//objects. Consider, more precisely, the event handlers's implementation details. Our
//event handler works as a state machine. In one state, we populate it with the Review objects, and in
//another one, with the Parser objects, and there are states for other events:
enum class HandlerState {
    None,
    Global,
    PapersArray,
    Paper,
    ReviewArray,
    Review
};

//Then, we declare a type for the object, which will be used by the parser to handle
//parsing events. This type should be inherited from the rapidjson::BaseReaderHandler base
// base class, and we need to override virtual handler function that the parser will call when
// a particular parsing event occurs, as illustrated in the following code block.


struct ReviewsHandler
    : public rapidjson::BaseReaderHandler<rapidjson::UTF8<>, ReviewsHandler>{

    //ctor:
    ReviewsHandler(Papers* papers): papers_(papers) {}

    //We parse the unsigned unit values only for the Id attributes of the Paper and the
    //Review objects, and we update these values according to the current parsed key, as follows:
    bool Uint (unsigned u){
        bool res{true};
        try {
            if(state_ == HandlerState::Paper && key_ == "id"){
                paper_.id = u;
            }else if (state_ == HandlerState::Review && key_ == "id"){
                review_.id = u;
            }else {
                res = false;
            }
        } catch (...) {
            res = false;
        }
        key_.clear();
        return res;
    }

    /*
    String values also exist in both types of objects, so we do the same checks to 
    update corresponding values, as follows:
    */
    bool String(const char* str, rapidjson::SizeType length, bool /*copy*/){
      bool res{true};
      try{
          if(state_ == HandlerState::Paper && key_ == "preliminary_decision") {
              paper_.preliminary_decision = std::string(str, length);
          } else if (state_ == HandlerState::Review && key_ == "confidence") {
             review_.confidence = std::string(str, length);
          } else if (state_ == HandlerState::Review && key_ == "evaluation") {
            review_.evaluation = std::string(str, length);
          }else if (state_ == HandlerState::Review && key_ == "lan"){
              review_.language = std::string(str, length);
          }else if (state_ == HandlerState::Review && key_ == "orientation"){
              review_.orientation = std::string(str, length);
          }else if (state_ == HandlerState::Review && key_ == "remarks"){
              review_.remarks = std::string(str, length);
          }else if (state_ == HandlerState::Review && key_ == "text"){
              review_.timespan = std::string(str, length);
          }else if ( state_ == HandlerState::Review && key_ == "timespan"){
              review_.timespan = std::string(str, length);
          }else{
              res = false;
          }
      
     }catch(...)
     {
         res = false;
     }
     key_.clear();
     return res;

    }


    // The event handler for the JSON key attribute stores the key value to the appropriate variable,
    // which we use to identify a current object in the parsing process, as follows:
    bool Key(const char* str, rapidjson::SizeType length, bool /*copy*/){
        key_ = std::string(str, length);
        return true;
    }

    /*
    The startObject event handler switches states according to the current key values and the previous state value.
    We bas ethe current implementation on the knowledge of the structure of the current JSON file: there is no array of Paper objects, 
    and each Paper object includes an array of reviews. It is one of the limitations of the SAX interface -- we need to know the structure of 
    the document to implement all event handlers correctly. The code could be seen in the following block:
    */
    bool StartObject() {
        if (state_ == HandlerState::None && key_.empty()){
            state_ = HandlerState::Global;
        } else if (state_ == HandlerState::PapersArray && key_.empty()){
            state_ = HandlerState::Paper;
        } else if (state_ == HandlerState::ReviewArray && key_.empty()){
            state_ = HandlerState::Review;
        }  else {
            return false;
        }
        return true;
    }


    /*
    In the EndObject event handler, we populate arrays of Paper and Review
    objects according to the current state. Also, we switch the current tstae
    back to the previous one by running the following code:
    */
    bool EndObject(rapidjson::SizeType /*memberCount*/){
        if (state_ == HandlerState::Global) {
            state_ = HandlerState::None;
        } else if (state_ == HandlerState::Paper){
            state_ = HandlerState::PapersArray;
            papers_->push_back(paper_);
            paper_ = Paper();
        } else if (state_ == HandlerState::Review) {
            state_ = HandlerState::ReviewArray;
            paper_.reviews.push_back(review_);
        } else {
            return false;
        }
        return true;
    }

    //In the StartArray event handler, we switch the current state to a new one according to
    //the current state value by running the following code:
    bool StartArray() {
        if(state_ == HandlerState::Global && key_ == "paper") {
            state_ = HandlerState::PapersArray;
            key_.clear();
        } else if (state_ == HandlerState::Paper && key_ == "review"){
            state_ = HandlerState::ReviewArray;
            key_.clear();
        } else {
            return false;
        }
        return true;
    }

    //In the EndArray event handler, we switch the current state to 
    bool EndArray(rapidjson::SizeType/*elementCount*/){
        if (state_ ==HandlerState::ReviewArray){
            state_ = HandlerState::Paper;
        } else if (state_ == HandlerState::PapersArray){
            state_ = HandlerState::Global;
        } else {
            return false;
        }
        return true;
    }

        Paper paper_;
        Review review_;
        std::string key_;
        Papers* papers_{nullptr};
        HandlerState state_{HandlerState::None};
    };


    //Notice that we made handlers only for objects and arrays parsing events, and events
    //for parsing unsigned int/string values. Now, we can create the
    //rapidjson::FileReadStream object as the argument to the Parse() method of the 
    //rapidjosn::Reader type object. The second agrument is the object of the type we derived from
    //rapidjson::BaseReaderHandler, as illustrated in the following code block:
    Papers ReadPapersReviews(const std::string& filename) {
        auto file = std::unique_ptr<FILE, void(*)(FILE*)>(
            fopen(filename.c_str(), "r"), [](FILE* f){
              if (f)
              ::fclose(f);   
            });
        if (file) {
          char readBuffer[65536];
          rapidjson::FileReadStream is(file.get(), readBuffer, sizeof(readBuffer));
          rapidjson::Reader reader;
          Papers papers;
          ReviewsHandler handler(&papers);
          auto res = reader.Parse(is, handler);
          if (!res) {
              throw std::runtime_error(rapidjson::GetParseError_En(res.Code()));
          }
          return papers;
        }
        else {
            throw std::invalid_argument("File cannot be openned " + filename);
        }
        
    }
    //fopen: http://www.cplusplus.com/reference/cstdio/fopen/
    /*
    If the file is successfully opened, the function returns a pointer to a FILE object that can be used to identify the stream on future operations.
      Otherwise, a null pointer is returned.
    */