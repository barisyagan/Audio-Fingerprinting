# Audio-Fingerprinting

Measuring Delay Between Streams Using Audio Fingerprinting

First, after compilation, we open Recorder. It needs one parameter;
desired start time for recording the voice in format HH:MM:SS.
To start the recordings in different computers at the same time, we
used Network Time Protocol. Program gets time using NTP from a public host and 
when matches with start time recording begins.
We record audio with sample rate of 44100hz and in a single channel (mono).
After 1 minute of recording, it converts raw output to WAV file. When recordings 
in two computers finished, we gather WAV files in one host and give them 
to calc-sound-delay program. This takes two audio files (WAV and many other formats 
that libsndfile library supports) and calculates the delay between inputs.
