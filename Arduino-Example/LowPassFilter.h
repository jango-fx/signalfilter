class LowPassFilter {

    double y, a, s;
    boolean initialized;
    
    void setAlpha(double alpha);
    void init(double alpha, double initval);
  public:
    LowPassFilter(double alpha);
    LowPassFilter(double alpha, double initval);
    double filter(double value);
    double filterWithAlpha(double value, double alpha);
    boolean hasLastRawValue(void);
    double lastRawValue(void);
};

void LowPassFilter::setAlpha(double alpha)  {
  if (alpha <= 0.0 || alpha > 1.0) {
    Serial.println("[1€-Filter]: alpha should be in (0.0, 1.0] and is now " + String(alpha)); // THROW EXCEPTION
  }
  a = alpha;
}

LowPassFilter::LowPassFilter(double alpha)  {
  init(alpha, 0);
}

LowPassFilter::LowPassFilter(double alpha, double initval)  {
  init(alpha, initval);
}

void LowPassFilter::init(double alpha, double initval)  {
  y = s = initval;
  setAlpha(alpha);
  initialized = false;
}

double LowPassFilter::filter(double value) {
  double result;
  if (initialized) {
    result = a * value + (1.0 - a) * s;
  } else {
    result = value;
    initialized = true;
  }
  y = value;
  s = result;
  return result;
}

double LowPassFilter::filterWithAlpha(double value, double alpha) {
  setAlpha(alpha);
  return filter(value);
}

boolean LowPassFilter::hasLastRawValue() {
  return initialized;
}

double LowPassFilter::lastRawValue() {
  return y;
}
