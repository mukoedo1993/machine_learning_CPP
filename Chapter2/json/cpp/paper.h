#ifndef PAPER_H
#define PAPER_H

#include "review.h"

#include <vector>
/*
Using a DOM for working with training datasets usu. requires a lot of memory
structures that are useless for machine learning algorithms. So, in many cases, 
it is preferable to use the SAX interface. It allows us to filter irrelevant data and initialize 
structures that we can use directly in our algorithms. In the following code sample, we use the 
approach.
*/

//As a preliminary step, we define types for paper/review entities, as follows:
struct Paper {
    uint32_t id{0};
    std::string preliminary_decision;
    std::vector<Review> reviews;
};

using Papers = std::vector<Paper>;

#endif  // PAPER_H