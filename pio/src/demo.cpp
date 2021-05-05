// #include <iostream>
// #include <vector>
// #include <cctype>
// #include <string>
// #include <sstream>
// #include <time.h>
// #include <SPI.h>
// #include <TJpg_Decoder.h>
// #include <SPIFFS.h>
// #include <Wire.h>
// #include <esp_now.h>
// #include <Pangodream_18650_CL.h>
// #include "helper/walk.h"
// #include <AnalogButtons.h>
// #include <Button2.h>
// #include <lvgl.h>
// #include <lv_examples.h>
// #include <lv_drv_conf.h>
// #include "WiFi.h"
// #include "../lib/TFT_eSPI-2.4.0-Beta/TFT_eSPI.h"
// #include <UtilityManager.h>
// #include <GamePadManager.h>
// // //#include <BreakOutGame.h>
// //#include <ESPNOW_Manager.h>

//   /*********************
//    *      DEFINES
//    *********************/

// #define SLEEP_GPIO_PIN  sleepPin
// #define BATTERY_GPIO_PIN  batteryPin
// #define BUTTON_GPIO_PIN  buttonPin
// #define WAKE_GPIO_PIN  wakePin

// const gpio_num_t sleepPin = GPIO_NUM_33;
// const gpio_num_t batteryPin = GPIO_NUM_39;
// const gpio_num_t buttonPin = GPIO_NUM_35;
// const gpio_num_t wakePin = GPIO_NUM_0;
// const gpio_num_t touch_cs = GPIO_NUM_21;

// ///////////////////////////////////////////////////////////////////
// //// BATTERY SETTINGS
// ///////////////////////////////////////////////////////////////////
// #define NB_ICON_WIDTH 3
// #define NB_ICON_HEIGHT 16
// #define NB_STATUS_HEIGHT_BAR NB_ICON_HEIGHT
// #define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
// #define NB_ICON_POS_X (TFT_WIDTH - NB_ICON_WIDTH)
// #define MIN_USB_VOL     4.9
// #define ADC_PIN         39
// #define CONV_FACTOR     1.8
// #define READS           20
// #define CHANNEL   3

//    /**********************
//     *      TYPEDEFS
//     **********************/

//     /**********************
//      *  STATIC PROTOTYPES
//      **********************/
// static void create_home(lv_obj_t* parent);
// static void create_chat(lv_obj_t* parent);
// static void create_gameshow(lv_obj_t* parent);
// static void create_system(lv_obj_t* parent);

// //static void battery_anim_cb(lv_task_t* t);
// static void home_kb_event_cb(lv_obj_t* ta, lv_event_t e);
// static void table_event_cb(lv_obj_t* chat_table, lv_event_t e);
// static void color_chg_event_cb(lv_obj_t* sw, lv_event_t e);

// //static void ta_event_cb(lv_obj_t* ta, lv_event_t e);

// /**********************
//  *  STATIC VARIABLES
//  **********************/
// int screenWidth = int(TFT_WIDTH);
// int screenHeight = int(TFT_HEIGHT);

// /* LVGL objects */
// // static lv_obj_t* tv;
// // static lv_obj_t* t1;
// // static lv_obj_t* t2;
// // static lv_obj_t* t3;
// static lv_style_t style_box;

// static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10];
// static lv_disp_buf_t disp_buf;

// /* Home Screen */
// static lv_obj_t* page_home;
// static lv_obj_t* home_bg_top;
// static lv_obj_t* home_bg_middle;
// static lv_obj_t* home_icons;
// static lv_obj_t* home_bg_bottom;
// static lv_obj_t* home_time_status;
// static lv_obj_t* home_fake_ta;
// static lv_obj_t* home_label_status;
// //static lv_obj_t* home_table;
// //static lv_obj_t* chat_bg_keyboard;
// //static lv_obj_t* chat_kb;
// //static lv_obj_t* chat_kb_ta;

// /* Chat Screen */
// static lv_obj_t* page_chat;
// static lv_obj_t* chat_bg_top;
// static lv_obj_t* chat_bg_middle;
// static lv_obj_t* chat_bg_bottom;
// static lv_obj_t* chat_bg_keyboard;
// static lv_obj_t* chat_kb;
// static lv_obj_t* chat_kb_ta;
// static lv_obj_t* chat_label_status;
// static lv_obj_t* chat_fake_ta;
// static lv_obj_t* chat_table;

// int itemIdx;

// /* ESPNOW Variables */
// enum Role { Primary, Secondary };
// Role role = Primary; // Select the role of this device
// esp_now_peer_info_t peer;

// unsigned long peer_ping_interval = 1 * 1000; // 1sec
// unsigned long peer_ping_lasttime = 0;
// unsigned long peer_check_interval = 3 * 1000; // 3sec
// unsigned long peer_last_packet_time = 0;

// /* OTHER */
// char* batteryImages[] = { "/battery_01.jpg", "/battery_02.jpg", "/battery_03.jpg", "/battery_04.jpg", "/battery_05.jpg" };


// /**********************
//  *      MACROS
//  **********************/

//  /**********************
//   *   GLOBAL FUNCTIONS
//   **********************/

// void lv_setup(void)
//       {
//       //tv = lv_tabview_create(lv_scr_act(), NULL);

//       if (LV_THEME_DEFAULT_INIT == lv_theme_material_init) {
//             lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
//             if (disp_size >= LV_DISP_SIZE_MEDIUM) {
//                   //lv_obj_set_style_local_pad_left(tv, LV_TABVIEW_PART_TAB_BG, LV_STATE_DEFAULT, LV_HOR_RES / 2);
//                   lv_obj_t* sw = lv_switch_create(lv_scr_act(), NULL);
//                   if (lv_theme_get_flags() & LV_THEME_MATERIAL_FLAG_DARK)
//                         lv_switch_on(sw, LV_ANIM_OFF);
//                   lv_obj_set_event_cb(sw, color_chg_event_cb);
//                   lv_obj_set_pos(sw, LV_DPX(10), LV_DPX(10));
//                   lv_obj_set_style_local_value_str(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, "Dark");
//                   lv_obj_set_style_local_value_align(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, LV_ALIGN_OUT_RIGHT_MID);
//                   lv_obj_set_style_local_value_ofs_x(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, LV_DPI / 35);
//                   }
//             }

//       lv_style_init(&style_box);
//       lv_style_set_value_align(&style_box, LV_STATE_DEFAULT, LV_ALIGN_OUT_TOP_LEFT);
//       lv_style_set_value_ofs_y(&style_box, LV_STATE_DEFAULT, -LV_DPX(10));
//       lv_style_set_margin_top(&style_box, LV_STATE_DEFAULT, LV_DPX(30));

//       //      t1 = lv_tabview_add_tab(tv, "Controls");
//       //      t2 = lv_tabview_add_tab(tv, "Visuals");
//       //      t3 = lv_tabview_add_tab(tv, "Selectors");

//       // controls_create(t1);
//       // visuals_create(t2);
//       // selectors_create(t3);
//       }

// ///////////////////////////////////////////////////////////////////
// // CONCRETE CLASSSES
// ///////////////////////////////////////////////////////////////////
// TFT_eSPI tft = TFT_eSPI();
// Pangodream_18650_CL BL(ADC_PIN, CONV_FACTOR, READS);
// //GamePadManager gamePad = GamePadManager(buttonPin);
// // UtilityManager uMan = UtilityManager();
// // ESPNOW_Manager esp_now = ESPNOW_Manager();
// // //XPT2046_Touchscreen ts(TFT_CS, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling
// // //digitalRainAnim.init(&tft, 3, 20, 3, 20, 60);


// ///////////////////////////////////////////////////////////////////
// // DISPLAY SETTINGS
// ///////////////////////////////////////////////////////////////////

// /* Display flushing */
// void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
//       {
//       uint16_t c;

//       tft.startWrite(); /* Start new TFT transaction */
//       tft.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1)); /* set the working window */
//       for (int y = area->y1; y <= area->y2; y++) {
//             for (int x = area->x1; x <= area->x2; x++) {
//                   c = color_p->full;
//                   tft.writeColor(c, 1);
//                   color_p++;
//                   }
//             }
//       tft.endWrite(); /* terminate TFT transaction */
//       lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
//       }

// bool my_touchpad_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data)
//       {
//       uint16_t touchX, touchY;

//       bool touched = tft.getTouch(&touchX, &touchY, 600);

//       if (!touched)
//             {
//             return false;
//             }

//       if (touchX > screenWidth || touchY > screenHeight)
//             {
//             Serial.println("Y or y outside of expected parameters..");
//             Serial.print("y:");
//             Serial.print(touchX);
//             Serial.print(" x:");
//             Serial.print(touchY);
//             }
//       else
//             {

//             data->state = touched ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
//             data->point.x = touchX;
//             data->point.y = touchY;
//             }

//       return false; /*Return `false` because we are not buffering and no more data to read*/
//       }


// // lv_indev_drv_t indev_keypad_drv;
// // lv_indev_drv_init(&indev_keypad_drv);             /*Descriptor of a input device driver*/
// // indev_drv.type = LV_INDEV_TYPE_KEYPAD;            /*Touch pad is a pointer-like device*/
// // indev_drv.read_cb = readGamePad;                  /*Set your driver function*/
// // lv_indev_drv_register(&indev_keypad_drv);         /*Finally register the driver*/

// bool readGamePad(lv_indev_drv_t* indev_keypad_drv, lv_indev_data_t* data)
//       {

//       return false;
//       /*Return `false` because we are not buffering and no more data to read*/
//       }

// /**********************************************
//  *  CALLBACKS
//  * ********************************************/

// static void scrollToEndOfTable() {
//       float tableHeight = lv_obj_get_height(chat_table);
//       printf("tableHeight: %f\n", tableHeight);
//       lv_page_scroll_ver(page_home, -tableHeight);
//       }

// static void updateTable(bool isMine, String msg) {
//       msg.trim();
//       if (msg.length() > 0) {
//             lv_table_set_row_cnt(chat_table, (itemIdx + 1));
//             lv_table_set_col_width(chat_table, itemIdx, LV_HOR_RES / 2 - 10);
//             lv_table_set_cell_align(chat_table, itemIdx, isMine ? 1 : 0, isMine ? LV_LABEL_ALIGN_RIGHT : LV_LABEL_ALIGN_LEFT);
//             lv_table_set_cell_value(chat_table, itemIdx, isMine ? 1 : 0, msg.c_str());
//             itemIdx++;
//             scrollToEndOfTable();
//             }
//       }

// bool sendMsgToPeer(uint8_t* peer_addr, String msg) {
//       byte byteMsg[msg.length() + 1];
//       msg.getBytes(byteMsg, msg.length() + 1);

//       esp_err_t result = esp_now_send(peer_addr, (uint8_t*)byteMsg, sizeof(byteMsg));

//       return !result;
//       }


// void checkPeerToSendMsg(String msg) {
//       msg.trim();
//       if (msg.length() == 0) {
//             return;
//             }

//       if (*peer.peer_addr == NULL) {
//             Serial.print("peer.peer_addr == NULL");
//             return;
//             }

//       bool sentResult = sendMsgToPeer(peer.peer_addr, msg);

//       if (sentResult) {
//             updateTable(true, msg);
//             }
//       }

// static void chat_keyboard_event_cb(lv_obj_t* chat_kb, lv_event_t event) {
//       lv_keyboard_def_event_cb(chat_kb, event);

//       if (event == LV_EVENT_APPLY) {
//             lv_obj_move_background(chat_bg_keyboard);
//             lv_obj_set_height(page_chat, 400);

//             //updateTable(true, lv_textarea_get_text(chat_kb_ta));
//             checkPeerToSendMsg(lv_textarea_get_text(chat_kb_ta));

//             scrollToEndOfTable();
//             lv_textarea_set_text(chat_kb_ta, "");

//             }
//       else if (event == LV_EVENT_CANCEL) {
//             lv_obj_move_background(chat_bg_keyboard);
//             lv_obj_set_height(page_chat, 400);
//             }
//       }


// static void color_chg_event_cb(lv_obj_t* sw, lv_event_t e)
//       {
//       if (LV_THEME_DEFAULT_INIT != lv_theme_material_init) return;
//       if (e == LV_EVENT_VALUE_CHANGED) {
//             uint32_t flag = LV_THEME_MATERIAL_FLAG_LIGHT;
//             if (lv_switch_get_state(sw)) flag = LV_THEME_MATERIAL_FLAG_DARK;

//             LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(), lv_theme_get_color_secondary(),
//                   flag,
//                   lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
//             }
//       }

// static void tab_changer_task_cb(lv_task_t* task) {
//       //       {
//       //       uint16_t act = lv_tabview_get_tab_act(tv);
//       //       act++;
//       //       if (act >= 3) act = 0;

//       //       lv_tabview_set_tab_act(tv, act, LV_ANIM_ON);

//       //       switch (act) {
//       //                   case 0:
//       //                         tab_content_anim_create(t1);
//       //                         break;
//       //                   case 1:
//       //                         tab_content_anim_create(t2);
//       //                         break;
//       //                   case 2:
//       //                         tab_content_anim_create(t3);
//       //                         break;
//       //             }
//       }

// static void makeKeyboard() {
//       chat_kb_ta = lv_textarea_create(chat_bg_keyboard, NULL);
//       lv_obj_set_size(chat_kb_ta, LV_HOR_RES, 40);
//       lv_obj_set_pos(chat_kb_ta, 0, 0);
//       lv_textarea_set_text(chat_kb_ta, "");

//       chat_kb = lv_keyboard_create(chat_bg_keyboard, NULL);
//       lv_obj_set_size(chat_kb, LV_HOR_RES, LV_VER_RES / 2);
//       lv_obj_set_pos(chat_kb, 0, 40);
//       lv_keyboard_set_cursor_manage(chat_kb, true);

//       lv_keyboard_set_textarea(chat_kb, chat_kb_ta);
//       lv_obj_set_event_cb(chat_kb, chat_keyboard_event_cb);
//       lv_obj_move_background(chat_bg_keyboard);
//       }

// static void updateTopStatus(lv_color_t color, String text) {
//       lv_obj_set_style_local_bg_color(chat_bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
//       lv_label_set_text(chat_label_status, text.c_str());
//       }

// // TODO FIX
// static void lv_page(void)
//       {
//       page_chat = lv_page_create(chat_bg_middle, NULL);
//       lv_obj_clean_style_list(page_chat, LV_OBJ_PART_MAIN);

//       lv_obj_set_size(page_chat, LV_HOR_RES, 400);
//       lv_obj_set_pos(page_chat, 0, 0);
//       //lv_page_set_edge_flash(page, true);

//       itemIdx = 0;

//       chat_table = lv_table_create(page_chat, NULL);
//       lv_obj_clean_style_list(chat_table, LV_OBJ_PART_MAIN);
//       lv_table_set_col_cnt(chat_table, 2);
//       lv_obj_set_pos(chat_table, 0, 0);
//       lv_obj_set_click(chat_table, false);
//       }

// // TODO FIX
// static void lv_page_home(void)
//       {
//       // page = lv_page_create(chat_bg_middle, NULL);
//       // lv_obj_clean_style_list(page, LV_OBJ_PART_MAIN);

//       // lv_obj_set_size(page, LV_HOR_RES, 400);
//       // lv_obj_set_pos(page, 0, 0);
//       // //lv_page_set_edge_flash(page, true);

//       // itemIdx = 0;

//       // home_table = lv_table_create(page, NULL);
//       // lv_obj_clean_style_list(home_table, LV_OBJ_PART_MAIN);
//       // lv_table_set_col_cnt(home_table, 2);
//       // lv_obj_set_pos(home_table, 0, 0);
//       // lv_obj_set_click(hoem_table, false);
//       }

// static void fake_ta_event_handler(lv_obj_t* obj, lv_event_t event)
//       {
//       if (event == LV_EVENT_CLICKED) {
//             lv_obj_move_foreground(chat_bg_keyboard);
//             //lv_obj_set_height(page, 180);
//             scrollToEndOfTable();
//             }
//       }

// /* ANIMATIONS */

// // static void battery_anim_cb(lv_task_t* t) {
// //       static uint32_t x = 0;
// //       lv_obj_t* batteryImages = t->im;
// //       if (x > sizeof(batteryImages)) x = 0;
// //       }

// ///////////////////////////////////////////////////////////////////
// // MENU SETTINGS
// ///////////////////////////////////////////////////////////////////

// static void create_chat() {

//       lv_obj_t* scr = lv_obj_create(NULL, NULL);
//       lv_scr_load(scr);

//       chat_bg_top = lv_obj_create(scr, NULL);
//       lv_obj_clean_style_list(chat_bg_top, LV_OBJ_PART_MAIN);
//       lv_obj_set_style_local_bg_opa(chat_bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       lv_obj_set_style_local_bg_color(chat_bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_YELLOW);
//       lv_obj_set_size(chat_bg_top, LV_HOR_RES, 30);

//       chat_label_status = lv_label_create(chat_bg_top, NULL);
//       lv_label_set_long_mode(chat_label_status, LV_LABEL_LONG_SROLL_CIRC);
//       lv_obj_set_width(chat_label_status, LV_HOR_RES - 20);
//       lv_label_set_text(chat_label_status, "TOP STATUS");
//       lv_obj_align(chat_label_status, NULL, LV_ALIGN_CENTER, 0, 0);

//       chat_bg_middle = lv_obj_create(scr, NULL);
//       lv_obj_clean_style_list(chat_bg_middle, LV_OBJ_PART_MAIN);
//       lv_obj_set_style_local_bg_opa(chat_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       lv_obj_set_style_local_bg_color(chat_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//       lv_obj_set_pos(chat_bg_middle, 0, 30);
//       lv_obj_set_size(chat_bg_middle, LV_HOR_RES, 400);

//       chat_bg_bottom = lv_obj_create(scr, NULL);
//       lv_obj_clean_style_list(chat_bg_bottom, LV_OBJ_PART_MAIN);
//       lv_obj_set_style_local_bg_opa(chat_bg_bottom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       lv_obj_set_style_local_bg_color(chat_bg_bottom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
//       lv_obj_set_pos(chat_bg_bottom, 0, 430);
//       lv_obj_set_size(chat_bg_bottom, LV_HOR_RES, 50);

//       chat_fake_ta = lv_textarea_create(chat_bg_bottom, NULL);
//       lv_textarea_set_text(chat_fake_ta, "Enter a message");
//       lv_obj_set_pos(chat_fake_ta, 0, 0);
//       lv_obj_set_size(chat_fake_ta, LV_HOR_RES, 50);
//       lv_obj_set_event_cb(chat_fake_ta, fake_ta_event_handler);

//       chat_bg_keyboard = lv_obj_create(scr, NULL);
//       lv_obj_clean_style_list(chat_bg_bottom, LV_OBJ_PART_MAIN);
//       lv_obj_set_style_local_bg_opa(chat_bg_keyboard, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       lv_obj_set_style_local_bg_color(chat_bg_keyboard, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//       lv_obj_set_pos(chat_bg_keyboard, 0, LV_VER_RES - (LV_VER_RES / 2 + 40));
//       lv_obj_set_size(chat_bg_keyboard, LV_HOR_RES, LV_VER_RES / 2 + 40);

//       lv_page();
//       makeKeyboard();
//       }

// static void create_gameshow() {
//       // lv_obj_t* scr = lv_obj_create(NULL, NULL);
//       // lv_scr_load(scr);

//       // chat_bg_top = lv_obj_create(scr, NULL);
//       // lv_obj_clean_style_list(chat_bg_top, LV_OBJ_PART_MAIN);
//       // lv_obj_set_style_local_bg_opa(chat_bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       // lv_obj_set_style_local_bg_color(chat_bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_YELLOW);
//       // lv_obj_set_size(chat_bg_top, LV_HOR_RES, 30);

//       // chat_label_status = lv_label_create(chat_bg_top, NULL);
//       // lv_label_set_long_mode(chat_label_status, LV_LABEL_LONG_SROLL_CIRC);
//       // lv_obj_set_width(chat_label_status, LV_HOR_RES - 20);
//       // lv_label_set_text(chat_label_status, "TOP STATUS");
//       // lv_obj_align(chat_label_status, NULL, LV_ALIGN_CENTER, 0, 0);

//       // chat_bg_middle = lv_obj_create(scr, NULL);
//       // lv_obj_clean_style_list(chat_bg_middle, LV_OBJ_PART_MAIN);
//       // lv_obj_set_style_local_bg_opa(chat_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       // lv_obj_set_style_local_bg_color(chat_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//       // lv_obj_set_pos(chat_bg_middle, 0, 30);
//       // lv_obj_set_size(chat_bg_middle, LV_HOR_RES, 400);

//       // chat_bg_bottom = lv_obj_create(scr, NULL);
//       // lv_obj_clean_style_list(chat_bg_bottom, LV_OBJ_PART_MAIN);
//       // lv_obj_set_style_local_bg_opa(chat_bg_bottom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       // lv_obj_set_style_local_bg_color(chat_bg_bottom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
//       // lv_obj_set_pos(chat_bg_bottom, 0, 430);
//       // lv_obj_set_size(chat_bg_bottom, LV_HOR_RES, 50);

//       // chat_fake_ta = lv_textarea_create(chat_bg_bottom, NULL);
//       // lv_textarea_set_text(chat_fake_ta, "Enter a message");
//       // lv_obj_set_pos(chat_fake_ta, 0, 0);
//       // lv_obj_set_size(chat_fake_ta, LV_HOR_RES, 50);
//       // lv_obj_set_event_cb(chat_fake_ta, fake_ta_event_handler);

//       // chat_bg_keyboard = lv_obj_create(scr, NULL);
//       // lv_obj_clean_style_list(chat_bg_bottom, LV_OBJ_PART_MAIN);
//       // lv_obj_set_style_local_bg_opa(chat_bg_keyboard, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       // lv_obj_set_style_local_bg_color(chat_bg_keyboard, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//       // lv_obj_set_pos(chat_bg_keyboard, 0, LV_VER_RES - (LV_VER_RES / 2 + 40));
//       // lv_obj_set_size(chat_bg_keyboard, LV_HOR_RES, LV_VER_RES / 2 + 40);

//       // lv_page_gameshow();
//       // makeKeyboard();
//       }

// static void create_system() {

//       // lv_obj_t* scr = lv_obj_create(NULL, NULL);
//       // lv_scr_load(scr);

//       // chat_bg_top = lv_obj_create(scr, NULL);
//       // lv_obj_clean_style_list(chat_bg_top, LV_OBJ_PART_MAIN);
//       // lv_obj_set_style_local_bg_opa(chat_bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       // lv_obj_set_style_local_bg_color(chat_bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_YELLOW);
//       // lv_obj_set_size(chat_bg_top, LV_HOR_RES, 30);

//       // chat_label_status = lv_label_create(chat_bg_top, NULL);
//       // lv_label_set_long_mode(chat_label_status, LV_LABEL_LONG_SROLL_CIRC);
//       // lv_obj_set_width(chat_label_status, LV_HOR_RES - 20);
//       // lv_label_set_text(chat_label_status, "TOP STATUS");
//       // lv_obj_align(chat_label_status, NULL, LV_ALIGN_CENTER, 0, 0);

//       // chat_bg_middle = lv_obj_create(scr, NULL);
//       // lv_obj_clean_style_list(chat_bg_middle, LV_OBJ_PART_MAIN);
//       // lv_obj_set_style_local_bg_opa(chat_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       // lv_obj_set_style_local_bg_color(chat_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//       // lv_obj_set_pos(chat_bg_middle, 0, 30);
//       // lv_obj_set_size(chat_bg_middle, LV_HOR_RES, 400);

//       // chat_bg_bottom = lv_obj_create(scr, NULL);
//       // lv_obj_clean_style_list(chat_bg_bottom, LV_OBJ_PART_MAIN);
//       // lv_obj_set_style_local_bg_opa(chat_bg_bottom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       // lv_obj_set_style_local_bg_color(chat_bg_bottom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
//       // lv_obj_set_pos(chat_bg_bottom, 0, 430);
//       // lv_obj_set_size(chat_bg_bottom, LV_HOR_RES, 50);

//       // chat_fake_ta = lv_textarea_create(chat_bg_bottom, NULL);
//       // lv_textarea_set_text(chat_fake_ta, "Enter a message");
//       // lv_obj_set_pos(chat_fake_ta, 0, 0);
//       // lv_obj_set_size(chat_fake_ta, LV_HOR_RES, 50);
//       // lv_obj_set_event_cb(chat_fake_ta, fake_ta_event_handler);

//       // chat_bg_keyboard = lv_obj_create(scr, NULL);
//       // lv_obj_clean_style_list(chat_bg_bottom, LV_OBJ_PART_MAIN);
//       // lv_obj_set_style_local_bg_opa(chat_bg_keyboard, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       // lv_obj_set_style_local_bg_color(chat_bg_keyboard, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//       // lv_obj_set_pos(chat_bg_keyboard, 0, LV_VER_RES - (LV_VER_RES / 2 + 40));
//       // lv_obj_set_size(chat_bg_keyboard, LV_HOR_RES, LV_VER_RES / 2 + 40);

//       // lv_page_system();
//       // //makeKeyboard();
//       }

// static void create_home() {

//       lv_obj_t* home_scr = lv_obj_create(NULL, NULL);
//       lv_scr_load(home_scr);

//       home_bg_top = lv_obj_create(home_scr, NULL);
//       lv_obj_clean_style_list(home_bg_top, LV_OBJ_PART_MAIN);
//       lv_obj_set_style_local_bg_opa(home_bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       lv_obj_set_style_local_bg_color(home_bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
//       lv_obj_set_size(home_bg_top, LV_HOR_RES, 30);

//       home_time_status = lv_label_create(home_bg_top, NULL);
//       lv_label_set_long_mode(home_time_status, LV_LABEL_LONG_SROLL_CIRC);
//       lv_obj_set_width(home_time_status, LV_HOR_RES - 20);
//       lv_label_set_text(home_time_status, "NixieBox");
//       lv_obj_align(home_time_status, NULL, LV_ALIGN_CENTER, 0, 0);

//       home_label_status = lv_label_create(home_bg_top, NULL);
//       lv_label_set_long_mode(home_label_status, LV_LABEL_LONG_SROLL_CIRC);
//       lv_obj_set_width(home_label_status, LV_HOR_RES - 20);
//       lv_label_set_text(home_label_status, "NixieBox");
//       lv_obj_align(home_label_status, NULL, LV_ALIGN_CENTER, 0, 0);

//       // /*Create an image object*/
//       // lv_obj_t* battery_animation = lv_img_create(lv_scr_act(), NULL);
//       // lv_anim_t battery_strenght_anim;
//       // lv_anim_value_t start = 0;
//       // lv_anim_value_t end = 4;

//       // lv_anim_init(&battery_strenght_anim);
//       // lv_anim_set_exec_cb(&battery_strenght_anim, (lv_anim_exec_xcb_t)battery_anim_cb);
//       // lv_anim_set_var(&battery_strenght_anim, battery_animation);
//       // lv_anim_set_time(&battery_strenght_anim, 3000);
//       // lv_anim_set_values(&battery_strenght_anim, start, end);
//       // //lv_anim_set_repeat_count(&battery_strenght_anim, LV_ANIM_REPEAT_INFINITE);
//       // lv_anim_start(&battery_strenght_anim);

//       home_bg_middle = lv_obj_create(home_scr, NULL);
//       lv_obj_clean_style_list(home_bg_middle, LV_OBJ_PART_MAIN);
//       lv_obj_set_style_local_bg_opa(home_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       lv_obj_set_style_local_bg_color(home_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//       lv_obj_set_pos(home_bg_middle, 0, 30);
//       lv_obj_set_size(home_bg_middle, LV_HOR_RES, 400);

//       home_icons = lv_btnmatrix_create(home_scr, NULL);
//       lv_obj_clean_style_list(home_bg_middle, LV_OBJ_PART_MAIN);
//       lv_obj_set_style_local_bg_opa(home_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       lv_obj_set_style_local_bg_color(home_bg_middle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//       lv_obj_set_pos(home_bg_middle, 0, 30);
//       lv_obj_set_size(home_bg_middle, LV_HOR_RES, 400);

//       home_bg_bottom = lv_obj_create(home_scr, NULL);
//       lv_obj_clean_style_list(home_bg_bottom, LV_OBJ_PART_MAIN);
//       lv_obj_set_style_local_bg_opa(home_bg_bottom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//       lv_obj_set_style_local_bg_color(home_bg_bottom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
//       lv_obj_set_pos(home_bg_bottom, 0, 430);
//       lv_obj_set_size(home_bg_bottom, LV_HOR_RES, 50);

//       lv_page_home();
//       }

// /*
//  * ESP-NOW TASK
//  */

// void sendPing() {
//       if (millis() > peer_ping_lasttime + peer_ping_interval) {

//             if (*peer.peer_addr != NULL) {
//                   byte pingByteMsg[1];
//                   String pingMsg = " ";
//                   pingMsg.getBytes(pingByteMsg, pingMsg.length());
//                   esp_now_send(peer.peer_addr, (uint8_t*)pingByteMsg, sizeof(pingByteMsg));
//                   }

//             peer_ping_lasttime = millis();
//             }
//       }

// void delPeer() {
//       esp_now_del_peer(peer.peer_addr);
//       }

// void checkLastPacket() {
//       if (*peer.peer_addr != NULL) {
//             unsigned long sinceLastPacket = millis() - peer_last_packet_time;
//             if (sinceLastPacket > peer_check_interval) {
//                   delPeer();
//                   *peer.peer_addr = NULL;
//                   updateTopStatus(LV_COLOR_ORANGE, "- Peer Disconnected! -");
//                   }
//             }
//       }

// void ScanForPeer() {

//       if (*peer.peer_addr != NULL) {
//             return;
//             }

//       int8_t scanResults = WiFi.scanNetworks();
//       if (scanResults > 0) {
//             for (int i = 0; i < scanResults; ++i) {
//                   String SSID = WiFi.SSID(i);
//                   String BSSIDstr = WiFi.BSSIDstr(i);
//                   vTaskDelay(10);

//                   if (SSID.indexOf("Peer") == 0) {
//                         int mac[6];
//                         if (6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5])) {
//                               char macAddr[6];
//                               sprintf(macAddr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

//                               esp_now_peer_info_t temp;
//                               memcpy(&temp.peer_addr, macAddr, 6);

//                               if (esp_now_is_peer_exist(temp.peer_addr)) {
//                                     Serial.println("Existed Peer!");
//                                     continue;
//                                     }

//                               memcpy(&peer.peer_addr, macAddr, 6);
//                               peer.channel = CHANNEL;
//                               peer.encrypt = 0;

//                               const esp_now_peer_info_t* peerNode = &peer;
//                               if (esp_now_add_peer(peerNode) != ESP_OK) {
//                                     Serial.println("Failed to add peer");
//                                     continue;
//                                     }

//                               updateTopStatus(LV_COLOR_SILVER, "- Connected -");
//                               checkPeerToSendMsg("Hello There~");
//                               }
//                         }
//                   }
//             }

//       WiFi.scanDelete();
//       vTaskDelay(1000);
//       }

// void configDeviceAP() {
//       String Prefix = "Peer:";
//       String Mac = WiFi.macAddress();
//       Serial.print("AP MAC: ");
//       Serial.println(Mac);

//       String SSID = Prefix + Mac;
//       String Password = "123456789";
//       bool result = WiFi.softAP(SSID.c_str(), Password.c_str(), CHANNEL, 0);
//       if (!result) {
//             Serial.println("AP Config failed.");
//             ESP.restart();
//             }
//       else {
//             Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
//             }
//       }

// void OnDataRecv(const uint8_t* mac_addr, const uint8_t* data, int data_len) {
//       if (role == Secondary && *peer.peer_addr == NULL) {
//             char macAddr[6];
//             sprintf(macAddr, "%02X:%02X:%02X:%02X:%02X:%02X", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//             memcpy(&peer.peer_addr, macAddr, 6);
//             peer.channel = CHANNEL;
//             peer.encrypt = 0;

//             const esp_now_peer_info_t* peerNode = &peer;
//             esp_err_t addStatus = esp_now_add_peer(peerNode);
//             if (addStatus == 0) {
//                   updateTopStatus(LV_COLOR_SILVER, "- Connected -");
//                   checkPeerToSendMsg("Hello Primary Peer!");
//                   }
//             }

//       String receivedString = (char*)data;
//       receivedString.trim();
//       if (receivedString.length() > 0) {
//             updateTable(false, receivedString);
//             }

//       peer_last_packet_time = millis();
//       }

// void InitESPNow() {
//       WiFi.disconnect();
//       if (esp_now_init() == 0) {
//             Serial.println("ESPNow Init Success");
//             updateTopStatus(LV_COLOR_CYAN, "- ESP-NOW READY -");
//             }
//       else {
//             Serial.println("ESPNow Init Failed");
//             ESP.restart();
//             }
//       }

// void espnowTask(void* pvParameters) {

//       vTaskDelay(1000);

//       if (role == Primary) {
//             Serial.println("[Primary Mode]");
//             WiFi.mode(WIFI_STA);
//             }
//       else {
//             Serial.println("[Secondary Mode]");
//             WiFi.mode(WIFI_AP_STA);
//             configDeviceAP();
//             }

//       InitESPNow();
//       esp_now_register_recv_cb(OnDataRecv);

//       while (1) {
//             if (role == Primary) {
//                   ScanForPeer();
//                   }
//             sendPing();
//             checkLastPacket();
//             vTaskDelay(50);
//             }
//       }

// void guiTask(void* pvParameters) {
//       lv_init();

//       tft.begin();
//       tft.setRotation(0);

//       uint16_t calData[5] = { 295, 3493, 320, 3602, 2 };
//       tft.setTouch(calData);

//       lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10);
//       lv_disp_drv_t disp_drv;
//       lv_disp_drv_init(&disp_drv);

//       disp_drv.hor_res = screenWidth;
//       disp_drv.ver_res = screenHeight;
//       disp_drv.flush_cb = my_disp_flush;
//       disp_drv.buffer = &disp_buf;
//       lv_disp_drv_register(&disp_drv);

//       lv_indev_drv_t indev_drv;
//       lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
//       indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
//       indev_drv.read_cb = my_touchpad_read;      /*Set your driver function*/
//       lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/

//       // lv_indev_drv_t indev_keypad_drv;
//       // lv_indev_drv_init(&indev_keypad_drv);             /*Descriptor of a input device driver*/
//       // indev_drv.type = LV_INDEV_TYPE_KEYPAD;            /*Touch pad is a pointer-like device*/
//       // indev_drv.read_cb = readGamePad;                  /*Set your driver function*/
//       // lv_indev_drv_register(&indev_keypad_drv);         /*Finally register the driver*/


//       lv_page();

//       while (1) {
//             lv_task_handler();
//             }
//       }

// #define NUM_MEMBERS		10
// #define PRINTSCANRESULTS 	1
// #define DATASIZE 			48

// uint8_t memberData = 0;
// esp_now_peer_info_t member;
// esp_now_peer_info_t members[NUM_MEMBERS] = {};
// //const esp_now_peer_info_t* peer = &member;
// int memberCount = 0;
// bool messageReceived = false;

// typedef struct struct_message {
//       const char* boardID;
//       const char* remoteAddress;
//       const char* message;
//       DateTime datetime_sent;
//       DateTime datetime_received;
//       } struct_message;

// struct_message msgOut;
// struct_message* msgIn;

// void EnrolMembers() {
//       memberData++;
//       for (int i = 0; i < memberCount; i++) {
//             const uint8_t* peer_addr = members[i].peer_addr;
//             if (i == 0) { // print only for first member
//                   Serial.print("Sending: ");
//                   Serial.println(memberData);
//                   }
//             esp_err_t result = esp_now_send(peer_addr, &memberData, sizeof(memberData));
//             Serial.print("Send Status: ");
//             if (result == ESP_OK) {
//                   Serial.println("Success");
//                   }
//             else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
//                   // How did we get so far!!
//                   Serial.println("ESPNOW not Init.");
//                   }
//             else if (result == ESP_ERR_ESPNOW_ARG) {
//                   Serial.println("Invalid Argument");
//                   }
//             else if (result == ESP_ERR_ESPNOW_INTERNAL) {
//                   Serial.println("Internal Error");
//                   }
//             else if (result == ESP_ERR_ESPNOW_NO_MEM) {
//                   Serial.println("ESP_ERR_ESPNOW_NO_MEM");
//                   }
//             else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
//                   Serial.println("Peer not found.");
//                   }
//             else {
//                   Serial.println("Not sure what happened");
//                   }
//             delay(100);
//             }
//       }

// // Scan for members in AP mode
// void ScanForMembers() {
//       int8_t scanResults = WiFi.scanNetworks();
//       // reset memebers
//       memset(members, 0, sizeof(members));
//       memberCount = 0;
//       Serial.println("");
//       if (scanResults == 0)  Serial.println("No Members Found");
//       else {
//             //Serial.print("Found "); Serial.print(scanResults); Serial.println(" devices ");
//             for (int i = 0; i < scanResults; ++i) {
//                   // Print SSID and RSSI for each device found
//                   String SSID = WiFi.SSID(i);
//                   int32_t RSSI = WiFi.RSSI(i);
//                   String BSSIDstr = WiFi.BSSIDstr(i);
//                   delay(10);

//                   std::string s = SSID.c_str();
//                   if (s.rfind("NIXIE", 0) == 0) {
//                         Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");

//                         // Get BSSID => Mac Address of the member
//                         int mac[6];
//                         if (6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]))
//                               {
//                               for (int ii = 0; ii < 6; ++ii) { members[memberCount].peer_addr[ii] = (uint8_t)mac[ii]; }
//                               }

//                         members[memberCount].channel = CHANNEL; // pick a channel
//                         members[memberCount].encrypt = 0; // no encryption
//                         memberCount++;
//                         Serial.println(memberCount + " New Members");
//                         }
//                   }
//             }

//       if (memberCount > 0) { Serial.print(memberCount); Serial.println(" member(s) found, processing.."); }
//       //else  { Serial.println("No member Found, trying again."); }

// // clean up ram
//       WiFi.scanDelete();
//       }

// // Check if the member is already paired with the master If not, pair the member with master
// void manageMembers() {

//       if (memberCount == 0) { return; }

//       for (int i = 0; i < memberCount; i++) {
//             Serial.print("Processing: ");
//             for (int ii = 0; ii < 6; ++ii) {
//                   Serial.print((uint8_t)members[i].peer_addr[ii], HEX);
//                   if (ii != 5) { Serial.print(":"); }
//                   }
//             Serial.print(" Status: ");

//             // check if the peer exists
//             bool exists = esp_now_is_peer_exist(members[i].peer_addr);
//             if (exists) { Serial.println("Already Paired"); }
//             else {
//                   // member not paired, attempt pair
//                   esp_err_t addStatus = esp_now_add_peer(&members[i]);
//                   if (addStatus == ESP_OK) {
//                         // Pair success
//                         Serial.println("Pair success");
//                         }
//                   else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
//                         // How did we get so far!!
//                         Serial.println("ESPNOW Not Init");
//                         }
//                   else if (addStatus == ESP_ERR_ESPNOW_ARG) {
//                         Serial.println("Add Peer - Invalid Argument");
//                         }
//                   else if (addStatus == ESP_ERR_ESPNOW_FULL) {
//                         Serial.println("Peer list full");
//                         }
//                   else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
//                         Serial.println("Out of memory");
//                         }
//                   else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
//                         Serial.println("Peer Exists");
//                         }
//                   else {
//                         Serial.println("Not sure what happened");
//                         }
//                   delay(100);
//                   }
//             }
//       }

// void setup() {
//       Serial.begin(115200);

//       xTaskCreate(guiTask, "gui", 4096 * 2, NULL, 2, NULL);
//       vTaskDelay(500);
//       xTaskCreate(espnowTask, "espnowTask", 4096, NULL, 1, NULL);
//       }

// void loop() {}