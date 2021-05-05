#ifndef UTILITYMANAGER_H
#define UTILITYMANAGER_H

//#include <DigitalRainAnim.h>
//#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <time.h>
#include <RTClib.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// static const char* TAG = "UtilityManager";

#define RIGHT_BUTTON_PIN 	35
#define LEFT_BUTTON_PIN  	0
#define BUTTON_PIN_BITMASK 	0x25 // 2^37 in hex
#define CHANNEL			3

class UtilityManager {

private:

	const char* ssid = "AlphaN5";
	const char* password = "TT-9058590898";
	const char* ssid_prefix = "NIXIEMASTER";

	// A utility function to swap to integers 
	void swap(int* a, int* b)
		{
		int temp = *a;
		*a = *b;
		*b = temp;
		}

	// A utility function to print an array 
	// void printArray(int arr[], int n)
	// 	{
	// 	for (int i = 0; i < n; i++)
	// 		cout << arr[i] << " ";
	// 	cout << "\n";
	// 	}

	// A function to generate a random 
	// permutation of arr[] 
	void randomize(int arr[], int n)
		{
		// Use a different seed value so that 
		// we don't get same result each time
		// we run this program 
		srand(time(NULL));

		// Start from the last element and swap 
		// one by one. We don't need to run for 
		// the first element that's why i > 0 
		for (int i = n - 1; i > 0; i--)
			{
			// Pick a random index from 0 to i 
			int j = rand() % (i + 1);

			// Swap arr[i] with the element 
			// at random index 
			swap(&arr[i], &arr[j]);
			}
		}

public:

	UtilityManager();
	~UtilityManager();

	DateTime getNow();
	void setupWifi();
	double ReadVoltage(gpio_num_t ADC_Pin);
	void triggerDeepSleep(gpio_num_t WAKE_PIN);
	void triggerLightSleep(gpio_num_t WAKE_PIN_2);
	void WakeUp(gpio_num_t WAKE_PIN);
	esp_sleep_wakeup_cause_t print_wakeup_reason();

	String mac2String(byte ar[]);
	int str2mac(const char* mac, uint8_t* values);

	int sort();

	bool incrementLeakyCounter();
	};
#endif