# fastQuantile
Implementation of the paper: A  Fast Algorithm for Approximate Quantiles in High Speed Data Streams

Estmating quantile function up to eps accuracy. If we're interested in quantile with precision up to 1%, eps can be set as 0.01.
Space complexity: O(log(eps*n)^2/eps), growing as O(log(n)^2), where n is the current array size.
Time complexity: each update operation (for any new incoming data) takes O(log(log(eps*n)/eps)) time, which is almost negligible.
