#include <deque>
#include <array>

class LogInterface {
public:


    virtual ~LogInterface() = default;

    //gamle metoder
    virtual std::deque<std::array<int, 4>> getHour() const = 0;  // retunerer seneste time med m�ling hver 5 min. hver plads har en array med  ph, fugt, lys, temp

    virtual std::deque<std::array<int, 4>> getday(int day) = 0; // idag = 0  ig�r =1  for en uge siden =6 , retunerer en dag med m�ling per time infor seneste uge

    virtual std::deque<std::array<int, 4>> getMonth() const = 0; // retunere den seneste m�ned med m�linger for hver dag




    // keywords for at f� fat i data

#define WATERLVL    0
#define MOIST       1
#define LIGHT       2
#define WEIGHT      3


    virtual void setLog(const std::array<int, 4>& values) = 0;   // opdaterer loggen med 1 m�ling fra 4 sensoer

    virtual void logClear() = 0;                                   // fjerner alt log

    virtual  std::array<int, 7>  getWeek(int type) const = 0; // reunerer seneste uge med m�ling for hver dag for en m�ledata ( fugt, v�gt osv)  som en int array. plads [0] er seneste

    virtual int getLatest(int type) const = 0;              // retunerer  seneste v�rdi for en  m�ledata som int

    virtual bool isEmpty() const = 0;                      // tjekker om vantaken er tom

};

class Log : public LogInterface {
public:
    Log() :LogInterface(), _hour(), _day(), _week(), _month() {};


    std::deque<std::array<int, 4>> getHour() const override {

        return _hour;
    }

    std::deque<std::array<int, 4>> getday(int day)  override {

        if (!_day.empty()) {
            _day.pop_back();
        }

        waterLevel, moisture, light, weight = 0;

        for (size_t i = (day * DAY); i < ((day * DAY) + DAY); i++)
        {

            waterLevel = _week[i][0];

            moisture = _week[i][1];

            light = _week[i][2];

            weight = _week[i][3];


            _day.push_front({ waterLevel, moisture, light, weight });

        }



        return _day;
    }

    std::array<int, 7> getWeek(int type) const override {


        std::array<int, 7> data = { -1,-1,-1,-1,-1,-1,-1 };

        int max = _month.size() > 7 ? 7 : _month.size();


        if (max != 0)
        {


            for (size_t i = 0; i < max; i++)
            {


                data[i] = _month[i][type];

            }

        }

        return data;

    }

    std::deque<std::array<int, 4>> getMonth() const override {

        return _month;
    }



    int getLatest(int type) const override {

        int latest = -1;

        if (!_hour.empty())
        {
            latest = _hour[0][type];
        }


        return latest;

    }

    bool isEmpty() const {

        if (_month.empty() && _hour.empty() && _day.empty() && _week.empty())
        {
            return true;
        }

        return   false;

    }


    void setLog(const std::array<int, 4>& values) override {


        // push hour

        _hour.push_front(values);

        m++;

        if (_hour.size() > 12)
            _hour.pop_back();


        //After full hour take avarage and push to week

        if (m == HOUR)
        {
            m = 0;

            waterLevel = 0; moisture = 0; light = 0; weight = 0;

            for (size_t i = 0; i < 12; i++)
            {

                waterLevel += _hour[i][0];

                moisture += _hour[i][1];

                light += _hour[i][2];

                weight += _hour[i][3];
            }

            _week.push_front({ waterLevel / HOUR,moisture / HOUR ,light / HOUR ,weight / HOUR });

            h++;

        }

        //After full Day take avarage and push it to month

        if (_day.size() > 24)
            _day.pop_back();

        if (h == DAY)
        {
            h = 0;

            waterLevel = 0; moisture = 0; light = 0; weight = 0;

            for (size_t i = 0; i < DAY; i++)
            {

                waterLevel += _week[i][0];

                moisture += _week[i][1];

                light += _week[i][2];

                weight += _week[i][3];
            }

            _month.push_front({ waterLevel / DAY,moisture / DAY ,light / DAY ,weight / DAY });


        }

        if (_month.size() > 30)
            _month.pop_back();


    }

    void logClear() override {
        // Implementation for clear() method


        _hour.clear();
        _day.clear();
        _week.clear();
        _month.clear();
    }

private:

    std::deque<std::array<int, 4>> _hour;
    std::deque<std::array<int, 4>> _day;
    std::deque<std::array<int, 4>> _week;
    std::deque<std::array<int, 4>> _month;

    static const int HOUR = 12;
    static const int  DAY = 24;
    static const int  WEEK = 7;
    static const int MAX_LOG_SIZE = 30;


    int m = 0, h = 0, d = 0;

    int waterLevel = 0, moisture = 0, light = 0, weight = 0;
};

