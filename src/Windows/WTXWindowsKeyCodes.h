

#if WT_OS_TYPE==OS_LINUX

/* These are the key codes converted from Windows virtual keys. All keys begin
    with KEY_ and end with either the long or short version of the key name  */
#define KEY_BACKSPACE (XK_BackSpace & 0xFF00)==0xFF00,XK_BackSpace&0xFF
#define KEY_TAB (XK_Tab & 0xFF00)==0xFF00,XK_Tab&0xFF

#define KEY_ENTER (XK_Return & 0xFF00)==0xFF00,XK_Return&0xFF
#define KEY_RETURN (XK_Return & 0xFF00)==0xFF00,XK_Return&0xFF

#define KEY_SHIFT (XK_Shift_L||XK_Shift_R & 0xFF00)==0xFF00,XK_Shift_L||XK_Shift_R&0xFF

#define KEY_CONTROL (XK_Control_L||XK_Control_R & 0xFF00)==0xFF00,XK_Control_L||XK_Control_R&0xFF
#define KEY_CTRL (XK_Control_L||XK_Control_R & 0xFF00)==0xFF00,XK_Control_L||XK_Control_R&0xFF

#define KEY_ALTERNATE (XK_Alt_L||XK_Alt_R & 0xFF00)==0xFF00,XK_Alt_L||XK_Alt_R&0xFF
#define KEY_ALT (XK_Alt_L||XK_Alt_R & 0xFF00)==0xFF00,XK_Alt_L||XK_Alt_R&0xFF

#define KEY_PAUSE (XK_Pause & 0xFF00)==0xFF00,XK_Pause&0xFF

#define KEY_CAPSLOCK (XK_Caps_Lock & 0xFF00)==0xFF00,XK_Caps_Lock&0xFF
#define KEY_CAPITALLOCK (XK_Caps_Lock & 0xFF00)==0xFF00,XK_Caps_Lock&0xFF

#define KEY_ESCAPE 1,XK_Escape&0xFF
#define KEY_ESC 1,XK_Escape&0xFF

#define KEY_SPACE 1,XK_space&0xFF

#define KEY_PGUP (XK_Page_Up & 0xFF00)==0xFF00,XK_Page_Up&0xFF
#define KEY_PAGEUP (XK_Page_Down & 0xFF00)==0xFF00,XK_Page_Down&0xFF

#define KEY_PGDN (XK_Page_Down & 0xFF00)==0xFF00,XK_Page_Down&0xFF
#define KEY_PAGEDOWN (XK_Page_Down & 0xFF00)==0xFF00,XK_Page_Down&0xFF

#define KEY_END (XK_End & 0xFF00)==0xFF00,XK_End&0xFF
#define KEY_HOME (XK_Home & 0xFF00)==0xFF00,XK_Home&0xFF

#define KEY_LEFT (XK_Left & 0xFF00)==0xFF00,XK_Left & 0xFF
#define KEY_LEFTARROW (XK_Left & 0xFF00)==0xFF00,XK_Left&0xFF

#define KEY_RIGHT (XK_Right & 0xFF00)==0xFF00,XK_Right & 0xFF
#define KEY_RIGHTARROW (XK_Right & 0xFF00)==0xFF00,XK_Right&0xFF

#define KEY_UP (XK_Up & 0xFF00)==0xFF00,XK_Up & 0xFF
#define KEY_UPARROW (XK_Up & 0xFF00)==0xFF00,XK_Up&0xFF

#define KEY_DOWN (XK_Down & 0xFF00)==0xFF00,XK_Down & 0xFF
#define KEY_DOWNARROW (XK_Down & 0xFF00)==0xFF00,XK_Down&0xFF

#define KEY_SELECT (XK_Select & 0xFF00)==0xFF00,XK_Select&0xFF

#define KEY_EARLYPRINT (XK_Print & 0xFF00)==0xFF00,XK_Print&0xFF
#define KEY_EARLYPRINTSCREEN (XK_Print & 0xFF00)==0xFF00,XK_Print&0xFF

#define KEY_EXECUTE (XK_Execute & 0xFF00)==0xFF00,XK_Execute&0xFF

#define KEY_PRINT (XK_Print & 0xFF00)==0xFF00,XK_Print&0xFF
#define KEY_PRINTSCREEN (XK_Print & 0xFF00)==0xFF00,XK_Print&0xFF

#define KEY_INS (XK_Insert & 0xFF00)==0xFF00,XK_Insert&0xFF
#define KEY_INSERT (XK_Insert & 0xFF00)==0xFF00,XK_Insert&0xFF

#define KEY_DEL (XK_Delete & 0xFF00)==0xFF00,XK_Delete&0xFF
#define KEY_DELETE (XK_Delete & 0xFF00)==0xFF00,XK_Delete&0xFF

#define KEY_HELP (XK_Help & 0xFF00)==0xFF00,XK_Help&0xFF

#define KEY_0 (XK_0 & 0xFF00)==0xFF00,XK_0&0xFF
#define KEY_1 (XK_1 & 0xFF00)==0xFF00,XK_1&0xFF
#define KEY_2 (XK_2 & 0xFF00)==0xFF00,XK_2&0xFF
#define KEY_3 (XK_3 & 0xFF00)==0xFF00,XK_3&0xFF
#define KEY_4 (XK_4 & 0xFF00)==0xFF00,XK_4&0xFF
#define KEY_5 (XK_5 & 0xFF00)==0xFF00,XK_5&0xFF
#define KEY_6 (XK_6 & 0xFF00)==0xFF00,XK_6&0xFF
#define KEY_7 (XK_7 & 0xFF00)==0xFF00,XK_7&0xFF
#define KEY_8 (XK_8 & 0xFF00)==0xFF00,XK_8&0xFF
#define KEY_9 (XK_9 & 0xFF00)==0xFF00,XK_9&0xFF

#define KEY_A (XK_A & 0xFF00)==0xFF00,XK_A&0xFF
#define KEY_B (XK_B & 0xFF00)==0xFF00,XK_B&0xFF
#define KEY_C (XK_C & 0xFF00)==0xFF00,XK_C&0xFF
#define KEY_D (XK_D & 0xFF00)==0xFF00,XK_D&0xFF
#define KEY_E (XK_E & 0xFF00)==0xFF00,XK_E&0xFF
#define KEY_F (XK_F & 0xFF00)==0xFF00,XK_F&0xFF
#define KEY_G (XK_G & 0xFF00)==0xFF00,XK_G&0xFF
#define KEY_H (XK_H & 0xFF00)==0xFF00,XK_H&0xFF
#define KEY_I (XK_I & 0xFF00)==0xFF00,XK_I&0xFF
#define KEY_J (XK_J & 0xFF00)==0xFF00,XK_J&0xFF
#define KEY_K (XK_K & 0xFF00)==0xFF00,XK_K&0xFF
#define KEY_L (XK_L & 0xFF00)==0xFF00,XK_L&0xFF
#define KEY_M (XK_M & 0xFF00)==0xFF00,XK_M&0xFF
#define KEY_N (XK_N & 0xFF00)==0xFF00,XK_N&0xFF
#define KEY_O (XK_O & 0xFF00)==0xFF00,XK_O&0xFF
#define KEY_P (XK_P & 0xFF00)==0xFF00,XK_P&0xFF
#define KEY_Q (XK_Q & 0xFF00)==0xFF00,XK_Q&0xFF
#define KEY_R (XK_R & 0xFF00)==0xFF00,XK_R&0xFF
#define KEY_S (XK_S & 0xFF00)==0xFF00,XK_S&0xFF
#define KEY_T (XK_T & 0xFF00)==0xFF00,XK_T&0xFF
#define KEY_U (XK_U & 0xFF00)==0xFF00,XK_U&0xFF
#define KEY_V (XK_V & 0xFF00)==0xFF00,XK_V&0xFF
#define KEY_W (XK_W & 0xFF00)==0xFF00,XK_W&0xFF
#define KEY_X (XK_X & 0xFF00)==0xFF00,XK_X&0xFF
#define KEY_Y (XK_Y & 0xFF00)==0xFF00,XK_Y&0xFF
#define KEY_Z (XK_Z & 0xFF00)==0xFF00,XK_Z&0xFF

#define KEY_a (XK_a & 0xFF00)==0xFF00,XK_a&0xFF
#define KEY_b (XK_b & 0xFF00)==0xFF00,XK_b&0xFF
#define KEY_c (XK_c & 0xFF00)==0xFF00,XK_c&0xFF
#define KEY_d (XK_d & 0xFF00)==0xFF00,XK_d&0xFF
#define KEY_e (XK_e & 0xFF00)==0xFF00,XK_e&0xFF
#define KEY_f (XK_f & 0xFF00)==0xFF00,XK_f&0xFF
#define KEY_g (XK_g & 0xFF00)==0xFF00,XK_g&0xFF
#define KEY_h (XK_h & 0xFF00)==0xFF00,XK_h&0xFF
#define KEY_i (XK_i & 0xFF00)==0xFF00,XK_i&0xFF
#define KEY_j (XK_j & 0xFF00)==0xFF00,XK_j&0xFF
#define KEY_k (XK_k & 0xFF00)==0xFF00,XK_k&0xFF
#define KEY_l (XK_l & 0xFF00)==0xFF00,XK_l&0xFF
#define KEY_m (XK_m & 0xFF00)==0xFF00,XK_m&0xFF
#define KEY_n (XK_n & 0xFF00)==0xFF00,XK_n&0xFF
#define KEY_o (XK_o & 0xFF00)==0xFF00,XK_o&0xFF
#define KEY_p (XK_p & 0xFF00)==0xFF00,XK_p&0xFF
#define KEY_q (XK_q & 0xFF00)==0xFF00,XK_q&0xFF
#define KEY_r (XK_r & 0xFF00)==0xFF00,XK_r&0xFF
#define KEY_s (XK_s & 0xFF00)==0xFF00,XK_s&0xFF
#define KEY_t (XK_t & 0xFF00)==0xFF00,XK_t&0xFF
#define KEY_u (XK_u & 0xFF00)==0xFF00,XK_u&0xFF
#define KEY_v (XK_v & 0xFF00)==0xFF00,XK_v&0xFF
#define KEY_w (XK_w & 0xFF00)==0xFF00,XK_w&0xFF
#define KEY_x (XK_x & 0xFF00)==0xFF00,XK_x&0xFF
#define KEY_y (XK_y & 0xFF00)==0xFF00,XK_y&0xFF
#define KEY_z (XK_z & 0xFF00)==0xFF00,XK_z&0xFF


/* have completed to end of the alphabet (would you believe it) so some keys
   still don't work, however keystore is large enough to take them all */
#endif
