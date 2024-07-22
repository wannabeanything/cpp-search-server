#include "request_queue.h"

int RequestQueue::GetNoResultRequests() const {
        int count = 0;
        
        for(const auto& request: requests_){
            if(request.found_document == false){
                ++count;
            }
            
        }
        return count;
}