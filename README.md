# Search Server

A document search engine written in C++17. It ranks documents by relevance using TF-IDF.

## Features

- Stop words, set at construction time.
- Minus-words in queries: documents containing them are excluded.
- Ranking by TF-IDF relevance, with rating as a tie-breaker.
- Filtering by document status or by a custom predicate.
- `MatchDocument`: shows which query words match a given document.
- `Paginator` for splitting results into pages.
- `RequestQueue`: counts queries with no results over a sliding window of 1440 requests (one day).
- Input validation: invalid words and document ids throw exceptions.

## Build and run

```
cd search-server
g++ -std=c++17 -O2 *.cpp -o search_server
./search_server
```

`main.cpp` is a demo: it adds five documents and sends a series of queries through `RequestQueue`.

## Project layout

- `search_server.h/.cpp`: the search engine itself.
- `request_queue.h/.cpp`: request statistics.
- `paginator.h`: pagination of results.
- `string_processing.h/.cpp`, `read_input_functions.h/.cpp`: helpers.
- `document.h/.cpp`: document and result types.
