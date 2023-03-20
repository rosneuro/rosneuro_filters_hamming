# ROSNeuro Hamming window

This ROSNeuro filter plugin applies an Hamming window to the provided data.

## Algorithm:
The filter applies the Hamming window to the data. The Hamming window is implemented as follows:
```cpp
	int nsamples;
	for(auto i = 0; i<nsamples; i++)
		window.at(i) = (54.0 - 46.0*cos((2.0 * M_PI * i)/(this->nsamples_-1))) / 100.0;
```
The provided window filters do not required mandatory parameters but the name and the type.
An example of the YAML configuration:
```
HammingCfgTest:
  name: hamming
  type: HammingWindowFloat
```
