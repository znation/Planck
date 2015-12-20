#include "mic.h"
#include "../constants.h"

#include <cassert>
#include <iostream>

static const size_t CHANNEL_COUNT = 2;
static const size_t FRAMES_PER_BUFFER = 200;

static int record( const void *inputBuffer,
        void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData ) {
  assert(framesPerBuffer == FRAMES_PER_BUFFER);
  Frame *m_frame = static_cast<Frame*>(userData);
  const float *rptr = static_cast<const float*>(inputBuffer);
  assert(CHANNEL_COUNT == 2);
  for (size_t i=0; i<FRAMES_PER_BUFFER; i++) {
    float left = *rptr++;
    float right = *rptr++;
    m_frame->insert(TimeDomainSample(left, right));
  }
  return 0;
}

static void handleError(PaError err) {
  if (err != paNoError) {
    Pa_Terminate();
    const char * errText = Pa_GetErrorText(err);
    throw errText;
  }
}

Mic::Mic() {
  // init microphone (input stream)
  PaStreamParameters inputParameters;
  handleError(Pa_Initialize());

  inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
  if (inputParameters.device == paNoDevice) {
    handleError(paInvalidDevice);
  }

  inputParameters.channelCount = CHANNEL_COUNT;                    /* stereo input */
  inputParameters.sampleFormat = paFloat32;
  inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
  inputParameters.hostApiSpecificStreamInfo = NULL;

  handleError(Pa_OpenStream(
    &m_stream,
    &inputParameters,
    NULL,                  /* &outputParameters, */
    SAMPLES_PER_SECOND,
    FRAMES_PER_BUFFER,
    paClipOff,      /* we won't output out of range samples so don't bother clipping them */
    record,
    static_cast<void *>(&m_frame) ));

  handleError(Pa_StartStream(m_stream));
}

Mic::~Mic() {
  // destroy microphone (stop recording)
  PaError err = Pa_CloseStream(m_stream);
  assert(err == paNoError);
  Pa_Terminate();
}

const Frame& Mic::sample() const {
  return m_frame;
}
