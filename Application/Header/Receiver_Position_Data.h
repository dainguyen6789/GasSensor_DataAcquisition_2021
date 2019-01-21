
//
#define num_of_elevation_stamp 11
#define num_of_azimuth_stamp 	10
#define Dai_to_JP_Zero 179;
#define declination_offset -0.4829;// calculate from data of 31July2018
//#define time_offset -1.14;// calculate from data of 31July2018
float date_azimuth_mapping[num_of_azimuth_stamp]={180,190,200,210,220,230,240,250,260,270};
//extern char  num_of_elevation_stamp=15;

float RX_pos[num_of_elevation_stamp][num_of_azimuth_stamp]=
{

	
		{119.82,119.61,118.85,118.38,117.44,116.11,112.12,104.72,77.73,95.33},
		{106.97,106.89,106.1,104.28,101.42,96.98,89.29,72.01,30.52,-86.15},
		{94.51,94.09,92.61,89.79,85.79,78.15,65.61,40.49,-15.02,-109.61},
		{81.95,81.37,79.12,75.23,69.43,58.96,42.8,12.22,-43.92,-119.48},
		{69.21,68.33,65.65,60.64,52.70,40.47,21.29,-11.06,-62.79,-124.79},
		{55.32,54.53,51.56,45.96,37.10,23.17,1.94,-30.27,-74.81,-126.08},
		{41.98,40.93,37.55,31.48,20.77,6.45,-15.44,-45.27,-83.60,-127.40},
		{28.32,26.99,23.19,16.38,6.05,-9.18,-30.43,-57.46,-91.05,-127.83},
		{14.10,12.88,8.80,0.00,-8.48,-23.52,-43.02,-68.15,-96.90,-127.34},
		{0.00,0.00,-5.75,-12.18,-22.67,-36.63,-54.72,-76.88,-101.31,-127.73},
		{-14.17,-15.05,-19.14,-26.37,-36.22,-48.72,-65.47,-83.89,-105.09,-127.49},
		//{-28.23,-29.54,-33.23,-39.61,-48.23,-60.09,-74.63,-90.88,-108.63,-127.54},
		//{-42.13,-43.09,-46.37,-52.16,-60.35,-70.52,-82.69,-96.78,-111.79,-127.76},
		//{-55.52,-56.40,-59.79,-65.01,-71.59,-80.18,-90.39,-101.91,-114.66,-127.95},
		//{-69.05,-70.14,-72.41,-76.53,-82.19,-89.29,-97.69,-106.82,-117.03,-128.06}


	
};
float RX_pos_test[4][num_of_azimuth_stamp]=
{
		{-28.23,-29.54,-33.23,-39.61,-48.23,-60.09,-74.63,-90.88,-108.63,-127.54},
		{-42.13,-43.09,-46.37,-52.16,-60.35,-70.52,-82.69,-96.78,-111.79,-127.76},
		{-55.52,-56.40,-59.79,-65.01,-71.59,-80.18,-90.39,-101.91,-114.66,-127.95},
		{-69.05,-70.14,-72.41,-76.53,-82.19,-89.29,-97.69,-106.82,-117.03,-128.06}
};
// Corrected sun time
float  elevation_stamp[num_of_elevation_stamp]={
	
2.2,
6.9,
11.6,
16.3,
21,
25.7,
30.4,
35.1,
39.8,
44.5,
49.2,
//53.9,
//58.6,
//63.3,
//68


};

float  elevation_stamp_test[4]={

53.9,
58.6,
63.3,
68


};


