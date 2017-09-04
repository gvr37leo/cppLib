#include <functional>
#include <vector>



struct TimedCallback{
private:
    struct TimedFunc{
        std::function<void()> callback;
        double timeLeft;
    
        TimedFunc(){}
    
        TimedFunc(std::function<void()> callback, double timeLeft){
            this->callback = callback;
            this->timeLeft = timeLeft;
        }
    };

public:
    static std::vector<TimedFunc> functionsToCall;

    TimedCallback() = delete;

    static void progress(double dt){
        for(int i = functionsToCall.size() - 1; i >= 0; i--){
            functionsToCall[i].timeLeft -= dt;
            if(functionsToCall[i].timeLeft <= 0){
                functionsToCall[i].callback();
                functionsToCall.erase(functionsToCall.begin() + i);
            }
        }
    }

    static void callAfterXSeconds(std::function<void()> callback, double wait){
        functionsToCall.emplace_back(TimedFunc(callback, wait));
    }
}

