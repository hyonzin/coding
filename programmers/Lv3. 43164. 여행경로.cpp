// https://programmers.co.kr/learn/courses/30/lessons/43164

#include <string>
#include <cstring>
#include <vector>

using namespace std;

typedef struct _Ticket {
    int to;
    char visited = 0;
    struct _Ticket* next = NULL;
} Ticket;

typedef struct _Airport {
    char name[4];
    struct _Ticket* ticket = NULL;
} Airport;

Airport airports[10000];
Ticket tickets[10000];
int Nairports = 0;
int Ntickets = 0;

int visits[10000];
//[10000]

int index(char* name) {
    int idx;
    
    for (idx=0; idx<Nairports; ++idx) {
        if (strcmp(airports[idx].name, name) == 0) return idx;
    }
    
    memcpy(airports[idx].name, name, 3);
    airports[idx].name[3] = '\0';
    Nairports++;
    
    return idx;
}

int check(int from, int n) {
    if (n == Ntickets) return 1;
    
    Ticket* ticket = airports[from].ticket;
    
    while (ticket != NULL) {
        if (ticket->visited) {
            ticket = ticket->next;
            continue;
        }
        
        visits[n] = ticket->to;
        ticket->visited = 1;
        if (check(ticket->to, n+1)) return 1;
        ticket->visited = 0;
        
        ticket = ticket->next;
    }
    return 0;
}

vector<string> solution(vector<vector<string>> _tickets) {
    vector<string> answer;
    int size = _tickets.size();
    
    // ICN: index 0
    index((char*)"ICN");
    
    for (int i=0; i<size; ++i) {
        int from = index((char*)_tickets[i][0].c_str());
        int to = index((char*)_tickets[i][1].c_str());

        if (airports[from].ticket == NULL) {
            airports[from].ticket = &tickets[Ntickets];
        } else {
            Ticket* prev = NULL;
            Ticket* ticket = airports[from].ticket;
            
            do {
                if (strcmp(airports[ticket->to].name,
                           airports[to].name) > 0) {
                    int swp = to;
                    to = ticket->to;
                    ticket->to = swp;
                }
                
                prev = ticket;
                ticket = ticket->next;
                
            } while(ticket != NULL);
            
            prev->next = &tickets[Ntickets];
        }
        
        tickets[Ntickets].to = to;
        Ntickets++;
    }
    
    check(0, 0);
    
    answer.push_back("ICN");
    for (int i=0; i<Ntickets; ++i) {
        answer.push_back(airports[visits[i]].name);
    }
    
    return answer;
}
