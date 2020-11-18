// Arrays
// PVectors
// Exceptions

class PVector {
    float x, y, z;
    public:
    array(float array[]){
      array[0] = x;
      array[1] = y;
      array[2] = z;}
};

class ArrayList {
    int s;
    public:
    int size() {
      return s;
    }
};

class SignalFilter {

    // Default Parameters of the OneEuroFilter
    // They can be changed using the corresponding setters
    double freq       = 120.0;
    double mincutoff  = 3.0;
    double beta_      = 0.007;
    double dcutoff    = 1.0;

    // Each SignalFilter can have a number of OneEuroFilter objects
    ArrayList channels;

    // Number of channels
    int size;

    // PRIVATE METHODS -------------------------------------------------------------------------
    void init(int channelCount);
    void createChannels(int channelCount);
    void filterValues(float noisyValues[], int size);
    PVector toVector(float array[], int size);

  public:
    // CONSTRUCTORS -------------------------------------------------------------------------
    SignalFilter();
    SignalFilter(int size);

    // PUBLIC METHODS -------------------------------------------------------------------------

    PVector SignalFilter::filterUnitVector(PVector noisyVector);
    float filterUnitFloat(float noisyFloat);
    void filterUnitArray(float noisyArray[], int size);
    PVector filterCoord2D( PVector noisyVector, float scaleX, float scaleY );
    PVector filterCoord2D( float coordX, float coordY, float scaleX, float scaleY );
    PVector filterCoord3D(PVector noisyVector, float scaleX, float scaleY, float scaleZ);
    PVector filterCoord3D( float coordX, float coordY, float coordZ, float scaleX, float scaleY, float scaleZ );
    void setFrequency(float f);
    void setMinCutoff(float mc);
    void setBeta(float b);
    void setDerivateCutoff(float dc);
};



// CONSTRUCTORS -------------------------------------------------------------------------

SignalFilter::SignalFilter() {
  init(1);                                                            // xxxxxxx EXCEPTION
}

SignalFilter::SignalFilter(int size) {
  if (size <= 0) {
    Serial.println("Error in SignalFilter(): The number of channels cannot be " + String(size) + ". The size should be at least 1");
  }

  init(size);                                                     // xxxxxxx EXCEPTION
}


// PUBLIC METHODS -------------------------------------------------------------------------

PVector SignalFilter::filterUnitVector(PVector noisyVector) {
  if (channels.size() < 3) {
    Serial.println("Error in filterUnit(): The number of channels cannot be " + String(size) + ". You need 3 channels to filter a PVector (even if you only use the x and y values).");
  }

  // Convert the source vector to an array
  float noisyValues[3];
  noisyVector.array(noisyValues);

  // Create the target array to receive the filtered values
  float filteredValues[3];
  filteredValues[0] = noisyValues[0];
  filteredValues[1] = noisyValues[1];
  filteredValues[2] = noisyValues[2];

  // Filter the noise and return an array of filtered values
  filterValues( filteredValues, 3 );                       // xxxxxxx EXCEPTION

  // Create the target vector to receive the filtered values
  PVector filteredVector = new PVector(0, 0, 0);

  // Convert the array to a PVector
  filteredVector = toVector(filteredValues);                          // xxxxxxx EXCEPTION

  // Return the filtered values
  return filteredVector;
}


float SignalFilter::filterUnitFloat(float noisyFloat) {
  // Create the source array to receive the source value
  float noisyArray[] = new float[1];

  // Create the target array to receive the filtered values
  float filteredArray[] = new float[1];

  // Pass the value to the array
  noisyArray[0] = noisyFloat;

  // Filter the noise and return an array of filtered values
  filteredArray = filterValues( noisyArray );                     // xxxxxxx EXCEPTION

  float filteredFloat = filteredArray[0];

  // Return the filtered value
  return filteredFloat;
}


void SignalFilter::filterUnitArray(float noisyArray[], int size) {
  // Get the size of the source array
  int valueCount = noisyArray.length;

  // Create the target array to receive the filtered values
  float filteredArray[] = new float[valueCount];

  // Filter the noise and return an array of filtered values
  try {
    filteredArray = filterValues( noisyArray );
  }
  catch (Exception e) {
    e.printStackTrace();
  }

  // Return the filtered values
  return filteredArray;
}

PVector SignalFilter::filterCoord2D( PVector noisyVector, float scaleX, float scaleY ) {
  PVector unitVector = new PVector(0, 0);

  // Convert the coordinate values to unit scale [0.0, 1.0]
  unitVector.x = noisyVector.x / scaleX;
  unitVector.y = noisyVector.y / scaleY;

  // Create the target vector and filter the noise
  PVector filteredVector = filterUnitVector( unitVector );

  // Scale the values back to the original coordinate system
  filteredVector.x = filteredVector.x * scaleX;
  filteredVector.y = filteredVector.y * scaleY;

  // Return the filtered values
  return filteredVector;

}

PVector SignalFilter::filterCoord2D( float coordX, float coordY, float scaleX, float scaleY ) {
  PVector unitVector = new PVector(0, 0);

  // Convert the coordinate values to unit scale [0.0, 1.0]
  unitVector.x = coordX / scaleX;
  unitVector.y = coordY / scaleY;

  // Create the target vector and filter the noise
  PVector filteredVector = filterUnitVector( unitVector );

  // Scale the values back to the original coordinate system
  filteredVector.x = filteredVector.x * scaleX;
  filteredVector.y = filteredVector.y * scaleY;

  // Return the filtered values
  return filteredVector;
}

PVector SignalFilter::filterCoord3D(PVector noisyVector, float scaleX, float scaleY, float scaleZ) {
  PVector unitVector = new PVector(0, 0, 0);

  // Convert the coordinate values to unit scale [0.0, 1.0]
  unitVector.x = noisyVector.x / scaleX;
  unitVector.y = noisyVector.y / scaleY;
  unitVector.z = noisyVector.z / scaleZ;

  // Create the target vector and filter the noise
  PVector filteredVector = filterUnitVector( unitVector );

  // Scale the values back to the original coordinate system
  filteredVector.x = filteredVector.x * scaleX;
  filteredVector.y = filteredVector.y * scaleY;
  filteredVector.z = filteredVector.z * scaleZ;

  // Return the filtered values
  return filteredVector;

}


PVector SignalFilter::filterCoord3D( float coordX, float coordY, float coordZ, float scaleX, float scaleY, float scaleZ ) {
  PVector unitVector = new PVector(0, 0);

  // Convert the coordinate values to unit scale [0.0, 1.0]
  unitVector.x = coordX / scaleX;
  unitVector.y = coordY / scaleY;
  unitVector.z = coordZ / scaleZ;

  // Create the target vector and filter the noise
  PVector filteredVector = filterUnitVector( unitVector );

  // Scale the values back to the original coordinate system
  filteredVector.x = filteredVector.x * scaleX;
  filteredVector.y = filteredVector.y * scaleY;
  filteredVector.z = filteredVector.z * scaleZ;

  // Return the filtered values
  return filteredVector;

}


void SignalFilter::setFrequency(float f) {
  // Store the value as double
  freq = (double) f;

  // Pass the value to all channels
  for (final OneEuroFilter filter : channels) {
    try {
      filter.setFrequency(freq);
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}

void SignalFilter::setMinCutoff(float mc) {
  // Store the value as double
  mincutoff = (double) mc;

  // Pass the value to all channels
  for (final OneEuroFilter filter : channels) {
    try {
      filter.setMinCutoff(mincutoff);
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}

void SignalFilter::setBeta(float b) {
  // Store the value as double
  beta_ = (double) b;

  // Pass the value to all channels
  for (final OneEuroFilter filter : channels) {
    try {
      filter.setBeta(beta_);
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}

void SignalFilter::setDerivateCutoff(float dc) {

  // Store the value as double
  dcutoff = (double) dc;

  // Pass the value to all channels
  for (final OneEuroFilter filter : channels) {
    try {
      filter.setDerivateCutoff(dcutoff);
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}



// PRIVATE METHODS -------------------------------------------------------------------------

void SignalFilter::init(int channelCount)  {
  if (channelCount <= 0) {
    throw new Exception("Exception in init(): The number of channels cannot be " + channelCount + ". The size should be at least 1");
  }
  try{
    createChannels(channelCount);
  }
  catch (Exception e) {
    e.printStackTrace();
  }
}


void SignalFilter::createChannels(int channelCount)   {
  if (channelCount <= 0) {
    throw new Exception("Exception in createChannels(): The number of channels cannot be " + channelCount + ". The size should be at least 1");
  }
  channels = new ArrayList<OneEuroFilter>(channelCount);
  for (int i = 0; i < channelCount; i++) {
    try {
      channels.add(new OneEuroFilter(freq, mincutoff, beta_, dcutoff)); // Create a default filter for this channel
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}


void SignalFilter::filterValues(float noisyValues[], int size) {
  // Save the amount of source values and channels array (they should match)
  int valueCount   = noisyValues.length;
  int channelCount = channels.size();

  if (valueCount != channelCount) {
    Serial.println("[1€-Filter] ERROR: Exception in filterValues(): The number of filtering channels (" + String(channelCount) + ") must match the number of signals you want to filter (" + String(valueCount) + ")");   // xxxxxxx EXCEPTION
  }

  // Create the array to return
  float filteredValues[valueCount];

  // Create timestamp
  double timestamp = myParent.frameCount / freq;

  // Get the filtered values for each noisy value
  for (int i = 0; i < valueCount; i++) {
    OneEuroFilter f = channels.get(i);
    double value = (double) noisyValues[i];
    filteredValues[i] = (float) f.filter(value, timestamp);
  }

  // Return the filtered values
  return filteredValues;
}

PVector SignalFilter::toVector(float[] array)  {
  int valueCount = array.length;

  if (valueCount > 3) {
    throw new Exception("Exception in toVector(): An array of length " + valueCount + " cannot be converted to PVector. The maximum number of values is 3");
  }
  else if (valueCount < 2) {
    throw new Exception("Exception in toVector(): An array of length " + valueCount + " cannot be converted to PVector. The minimum number of values is 2");
  }

  float[] a = array;

  // Convert the array back to a PVector
  float x = a[0];
  float y = a[1];
  float z = a[2];
  PVector v = new PVector(x, y, z);

  // Return the resulting PVector
  return v;
}
