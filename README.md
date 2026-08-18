# advanced_bitscrambler
Processing of bitwise logical operation among two channels where the bitwise function is stored within 3rd channel using bitscrambler on esp32 p4 allowing universal per pixel logic function.

This component for esp32p4 is created mainly as a RFE to Espressif and necessary silicon upgrades for gathering 10 times boost in performances when implementation solutions are based on the STATE paradigm, bitscrambler itself is built on. The necessary changes are related to partitioning of COUNTER A existing in bitscrambler to be able to behave like several smaller counters of only: single, two , three or or four bits wide independently in indexed addressing.

For better understanding of the STATE paradigm, here is detailed explanation:

https://drive.google.com/file/d/1AKL6803X-X7vca3wQiHR9chXjXsqHdxL/view?usp=drive_link

Demo application using existing implementation is included with component and detailed explanation in .bsasm file  

