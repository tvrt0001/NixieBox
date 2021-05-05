// #ifndef __GAMEPADMANAGER_H__
// #define __GAMEPADMANAGER_H__

// #include <lvgl.h>
// #include <lv_examples.h>
// #include <stdio.h>

// //Button
// //class ButtonMatrices : friend GamePadManager{

// //public:


// static void event_handler(lv_obj_t* obj, lv_event_t event)
// 	{
// 	if (event == LV_EVENT_VALUE_CHANGED) {
// 		const char* txt = lv_btnmatrix_get_active_btn_text(obj);

// 		printf("%s was pressed\n", txt);
// 		}
// 	}


// static const char* btnm_home_map[] = { "GsmeShow", "", "3", "4", "5", "\n",
// 						"6", "7", "8", "9", "0", "\n",
// 						"Action1", "Action2", "" };

// void lv_ex_btnmatrix_Home(void)
// 	{
// 	lv_obj_t* btnm1 = lv_btnmatrix_create(lv_scr_act(), NULL);
// 	lv_btnmatrix_set_map(btnm1, btnm_home_map);
// 	lv_btnmatrix_set_btn_width(btnm1, 10, 2);        /*Make "Action1" twice as wide as "Action2"*/
// 	lv_btnmatrix_set_btn_ctrl(btnm1, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
// 	lv_btnmatrix_set_btn_ctrl(btnm1, 11, LV_BTNMATRIX_CTRL_CHECK_STATE);
// 	lv_obj_align(btnm1, NULL, LV_ALIGN_CENTER, 0, 0);
// 	lv_obj_set_event_cb(btnm1, event_handler);
// 	}

// // 	};
// // #endif

// class GamePadManager
// 	{
// 	private:
// 		AnalogButtons _buttons;

// 		int _currentPage = 0;
// 		int _numScreens = 5;
// 		int _maxScreen = _numScreens - 1;
// 		int _pressedButtonNumber;
// 		bool _buttonPressed = false;
// 		int _debounce = 5;
// 		int _margin = 100;

// 		//AnalogButtons _buttons;
// 		gpio_num_t _pinNumber;

// 		// int _debounce;
// 		// int _margin;

// 		void configure() {
// 			unsigned int value = analogRead(_pinNumber);
// 			Serial.println(value);
// 			delay(250);
// 			}

// 		void left_b_Click() {
// 			Serial.println("left clicked");
// 			_pressedButtonNumber = 0;
// 			switch (_currentPage) {
// 					case 0:
// 						//drawChatScreen();
// 						//showPages();
// 						break;
// 					case 1:
// 						break;
// 					case 2:
// 						break;
// 					case 3:
// 						break;
// 				}
// 			}
// 		void left_b_Hold() {
// 			Serial.println("left held");
// 			_pressedButtonNumber = 0; _buttonPressed = true;

// 			switch (_currentPage) {
// 					case 0:
// 						//drawChatScreen();
// 						//showPages();
// 						break;
// 					case 1:
// 						break;
// 					case 2:
// 						break;
// 					case 3:
// 						break;
// 				}
// 			//showBootScreen();
// 			}

// 		// SEND MAIL
// 		// up_b_ = UpButton
// 		void up_btn_Click() {
// 			Serial.println("up clicked");
// 			switch (_currentPage) {
// 					case 0:
// 						//drawChatScreen();
// 						//showPages();
// 						break;
// 					case 1:
// 						break;
// 					case 2:
// 						break;
// 					case 3:
// 						break;
// 				}
// 			}
// 		void up_btn_Hold() {
// 			Serial.println("up held");
// 			_pressedButtonNumber = 1; _buttonPressed = true;
// 			switch (_currentPage) {
// 					case 0:
// 						//drawChatScreen();
// 						//showPages();
// 						break;
// 					case 1:
// 						break;
// 					case 2:
// 						break;
// 					case 3:
// 						break;
// 				}
// 			// if (esp_now.hasUnreadMail()) {
// 			// 	esp_now.mailReceived();
// 			// 	}
// 			}


// 		void right_btn_Click() {
// 			Serial.println("right clicked");
// 			switch (_currentPage) {
// 					case 0:
// 						//processMenu(3);
// 						//drawChatScreen();
// 					//showPages();
// 						break;
// 					case 1:
// 						break;
// 					case 2:
// 						break;
// 					case 3:
// 						break;
// 				}
// 			}
// 		void right_btn_Hold() {
// 			Serial.println("right held");
// 			_pressedButtonNumber = 2; _buttonPressed = true;
// 			switch (_currentPage) {
// 					case 0:
// 						//drawChatScreen();
// 						//showPages();
// 						break;
// 					case 1:
// 						break;
// 					case 2:
// 						break;
// 					case 3:
// 						break;
// 				}
// 			//breakout.initgame();
// 			// drawShapes();
// 			}

// 		void downt_btn_Click() {
// 			switch (_currentPage) {
// 					case 0:
// 						//drawChatScreen();
// 						//showPages();
// 						break;
// 					case 1:
// 						break;
// 					case 2:
// 						break;
// 					case 3:
// 						break;
// 				}
// 			}

// 		void downt_btn_Hold() {
// 			Serial.println("down held");
// 			_pressedButtonNumber = 3; _buttonPressed = true;
// 			switch (_currentPage) {
// 					case 0:
// 						break;
// 					case 1:
// 						break;
// 					case 2:
// 						break;
// 					case 3:
// 						break;
// 				}
// 			}

// 		void select_btn_Click() {
// 			Serial.println("select clicked");
// 			switch (_currentPage) {

// 					case 0:
// 						//startApp(_currentPage, lastButtonPressed);
// 						break;
// 					case 1:
// 						//showChatScreen();
// 						break;
// 					case 2:
// 						//drawBirdGame();
// 						//j = -8;
// 						break;
// 					case 3:
// 						//drawShapes();
// 						break;
// 					case 4:
// 						break;
// 					case 5:
// 						//showSystemPrefs();
// 						break;
// 				}
// 			}
// 		void select_btn_Hold() {
// 			Serial.println("select held");
// 			_pressedButtonNumber = 4; _buttonPressed = true;

// 			if (_pressedButtonNumber == 4 && _buttonPressed) {
// 				//drawHomeScreen();
// 				}

// 			switch (_currentPage) {
// 					case 0:
// 						break;
// 					case 1:
// 						break;
// 					case 2:
// 						//startBirdGame();
// 						break;
// 					case 3:
// 						break;
// 				}
// 			}

// 	public:



// 		~GamePadManager();

// 		GamePadManager(gpio_num_t buttonPinNumber) {

// 			_currentPage = 0;
// 			_numScreens = 5;
// 			_maxScreen = _numScreens - 1;
// 			_pressedButtonNumber = 0;
// 			_buttonPressed = false;
// 			_debounce = 5;
// 			_margin = 100;
// 			_pinNumber = buttonPinNumber;

// 			_buttons = AnalogButtons(buttonPinNumber, INPUT, _debounce, _margin);
// 			//LoadButtons();
// 			}

// 		Button left_btn = Button(0, &left_b_Click, &left_b_Hold, 1000, 150);                // LEFT = 0
// 		Button up_btn = Button(400, &up_btn_Click, &up_btn_Hold, 1000, 150);                // UP = 362 - 446
// 		Button down_btn = Button(1150, &downt_btn_Click, &downt_btn_Hold, 1000, 150);       // DOWN = 1199 - 1104
// 		Button right_btn = Button(1775, &right_btn_Click, &right_btn_Hold, 1500, 150);      // RIGHT = 1819 - 1758
// 		Button select_btn = Button(2620, &select_btn_Click, &select_btn_Hold, 1000, 500);   // SELECT = 2719 - 2666
// 		_buttons.add(left_btn);
// 		_buttons.add(up_btn);
// 		_buttons.add(down_btn);
// 		_buttons.add(right_btn);
// 		_buttons.add(select_btn);


// 		void ProcessMenu(int _pressedButtonNumber, bool wasHeld = false) {

// 			//if (lastButtonPressed == _buttonPressed) 
// 				//break;

// 			switch (_pressedButtonNumber) {
// 					case 1:
// 						_currentScreen--;
// 						break;
// 					case 3:
// 						_currentScreen++;
// 						break;
// 					case 5:
// 						//startAPP();
// 						break;
// 				}

// 			// if (_currentScreen < _maxScreen) _currentScreen = 0;
// 			// if (_currentScreen > 0) _currentScreen = _maxScreen;

// 			//showChatScreen();
// 			}

// 		// LEFT -   SHOW BOOT		// UP -     SEND MAIL
// 		// RIGHT -  Draw Shapes		// DOWN - 
// 		// SELECT - BirdGame

// 		// int _pressedButtonNumber = -1;
// 		// bool _buttonPressed = false;

// 	};

// #endif // __GAMEPADMANAGER_H__