#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Request {
    int from;
    int to;
    int begin;
    int end;

    friend istream& operator>>(istream& is, Request& request);
};

istream& operator>>(istream& is, Request& request) {
    is >> request.from >> request.to >> request.begin >> request.end;
    return is;
}

Request readRequest(istream& is) {
    Request request;
    is >> request;
    return request;
}

vector<Request> readRequests(istream& is, int requestCount) {
    vector<Request> requests(requestCount);
    for (size_t i = 0; i < requestCount; ++i) {
        is >> requests[i];
    }
    return requests;
}

vector<int> readChancksOnServers(istream& is, int chancksCount){
    vector<int> chancksOnServers(chancksCount);
    for (int i = 0; i < chancksCount; ++i) {
        is >> chancksOnServers[i];
    }
    return chancksOnServers;
}

bool requestProcessing(const Request& request, vector<int>& chancksOnServers) {
    for (int i = request.begin - 1; i <= request.end - 1; ++i) {
        if (chancksOnServers[i] != request.from)
            return false;
    }

    for (int i = request.begin-1; i <= request.end-1; ++i) {
        chancksOnServers[i] = request.to;
    }

    return true;
}

vector<bool> requestsProcessing(const vector<Request>& requests, vector<int>& chancksOnServers) {
    vector<bool> results(requests.size());

    for (int i = 0; i < requests.size(); ++i) {
        results[i] = requestProcessing(requests[i], chancksOnServers);
    }

    return results;
}

void processingInputData(istream& is) {
    int n, m, q;
    is >> n >> m >> q;

    vector<int> chancksOnServers = readChancksOnServers(is, n);
    vector<Request> requests = readRequests(is, q);

    vector<bool> results = requestsProcessing(requests, chancksOnServers);

    for (auto res : results) {
        cout << static_cast<int>(res) << endl;
    }
}

int main()
{
    {
        stringstream ss{ "1 2 1\n1\n1 2 1 1" };
        processingInputData(ss);
        cout << endl;
    }
    {
        stringstream ss{ "1 2 1\n1\n2 1 1 1" };
        processingInputData(ss);
        cout << endl;
    }
    {
        stringstream ss{ "5 5 6\n1 2 3 4 5\n1 2 1 1\n2 3 1 3\n4 2 4 4\n2 5 1 4\n3 2 2 3\n3 2 3 3" };
        processingInputData(ss);
        cout << endl;
    }

    system("pause");
    return 0;
}