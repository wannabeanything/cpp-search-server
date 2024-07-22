#pragma once
#include <deque>
#include "search_server.h"


class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server) 
    : ss_(search_server) 
    {
        
    }
    
    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    vector<Document> AddFindRequest(const string& raw_query, DocumentPredicate document_predicate) {
        ++current_time_;
        auto result = ss_.FindTopDocuments(raw_query, document_predicate);
        if(!result.empty()){
            requests_.push_back({true, raw_query});
        }
        else{
            requests_.push_back({false, raw_query});
            
        }
        while(current_time_ > min_in_day_){
            requests_.pop_front();
            --current_time_;
        }
        return result;
    }
    vector<Document> AddFindRequest(const string& raw_query, DocumentStatus status) {
        return AddFindRequest(raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
            return document_status == status;
        });
    }
    vector<Document> AddFindRequest(const string& raw_query) {
        return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
    }
    int GetNoResultRequests() const;
private:
    struct QueryResult {
        bool found_document;
        string query;    
    };
    const SearchServer& ss_;
    int current_time_ = 0;
    deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    
};