# fastQuantile
We provide a highly efficient quantile approximator for high speed large data stream. Only O(log(n)^2) memory is required for in RAM computation where n is the stream size. 

The C++ class CSummary in fastQ.hpp implements the paper A Fast Algorithm for Approximate Quantiles in High Speed Data Streams (Qi Zhang and Wei Wang 2007). This data structure helps estimate quantile function up to eps accuracy. If we're interested in quantile with precision up to 1%, eps can be set as 0.01. For fixed eps, such as eps=0.01, the space and time complexity are listed below.

|         Space complexity          | O(log(n)^2)    |
| :-------------------------------: | -------------- |
| Time complexity for single update | O(log(log(n))) |
| Time complexity for single query  | O(log(log(n))) |

Demos and tests can be found in fastQ.cpp.