#include <chrono>
#include <iomanip>
#include <iostream>

using forecast_time = std::chrono::time_point<std::chrono::system_clock>;
using namespace std::chrono_literals;

class Forecast {
public:
  virtual double getConfidence() const { return 0.0; }
  virtual std::string getForecast() const {
    return "Reply hazy, try again.";
  };

  virtual forecast_time getStart() const = 0;
  virtual forecast_time getEnd() const = 0;
};

class OneDayForecast : public Forecast {
public:
  OneDayForecast(const std::string &forecast, const forecast_time &start)
      : m_forecast{forecast}, m_start{start}, m_end{start + forecast_time::duration{24h}} {}
  virtual forecast_time getStart() const override {
    return m_start;
  }
  virtual forecast_time getEnd() const override {
    return m_end;
  }
  virtual std::string getForecast() const override {
    std::stringstream ss{};
    auto local_start{(std::chrono::system_clock::to_time_t(m_start))};
    auto local_end{(std::chrono::system_clock::to_time_t(m_end))};
    ss << "Between "
       << std::put_time(std::localtime(&local_start), "%b %d, %y at %H:%M:%S")
       << " and "
       << std::put_time(std::localtime(&local_end), "%b %d, %y at %H:%M:%S")
       << ", the weather will be " << m_forecast << ".";
    return ss.str();
  }
  virtual double getConfidence() const override { return 50.0; };

private:
  forecast_time m_start;
  forecast_time m_end;
  std::string m_forecast;
};

class TenDayForecast : public Forecast {
public:
  TenDayForecast(const std::string &forecast, const forecast_time &start)
      : m_forecast{forecast}, m_start{start}, m_end{start + forecast_time::duration{10*24h}} {}
  virtual forecast_time getStart() const override {
    return m_start;
  }
  virtual forecast_time getEnd() const override {
    return m_end;
  }
  virtual std::string getForecast() const override {
    std::stringstream ss{};
    auto local_start{(std::chrono::system_clock::to_time_t(m_start))};
    auto local_end{(std::chrono::system_clock::to_time_t(m_end))};
    ss << "Between "
       << std::put_time(std::localtime(&local_start), "%b %d, %y at %H:%M:%S")
       << " and "
       << std::put_time(std::localtime(&local_end), "%b %d, %y at %H:%M:%S")
       << ", the weather will be " << m_forecast << ".";
    return ss.str();
  }

private:
  forecast_time m_start;
  forecast_time m_end;
  std::string m_forecast;
};

void weather_authority(const Forecast &forecast) {
  std::cout << "The Local 12 Weather authority forecast:\n";
  std::cout << forecast.getForecast() << "\n";
}

int main() {
  forecast_time now{std::chrono::system_clock::now()};
  OneDayForecast san_diego{"Nice", now};
  TenDayForecast cincinnati{"¯\\_(ツ)_/¯", now};

  weather_authority(cincinnati);
  weather_authority(san_diego);
  return 0;
}