

#if WT_OS_TYPE==OS_LINUX

// These are the key codes converted from Windows virtual keys. All keys begin with KEY_ and end with either the long or short version of the key name

#define KEY_CODE_BACKSPACE (XK_BackSpace&0xFF)
#define KEY_CODE_TAB (XK_Tab&0xFF)

#define KEY_CODE_ENTER (XK_Return&0xFF)
#define KEY_CODE_RETURN (XK_Return&0xFF)

#define KEY_CODE_LEFT_SHIFT (XK_Shift_L&0xff)
#define KEY_CODE_RIGHT_SHIFT (XK_Shift_R&0xff)

#define KEY_CODE_LEFT_CONTROL (XK_Control_L&0xff)
#define KEY_CODE_RIGHT_CONTROL (XK_Control_R&0xff)
#define KEY_CODE_LCTRL (XK_Control_L&0xff)
#define KEY_CODE_RCTRL (XK_Control_R&0xff)

#define KEY_CODE_LEFT_ALTERNATE (XK_Alt_L&0xff)
#define KEY_CODE_RIGHT_ALTERNATE (XK_Alt_R&0xff)
#define KEY_CODE_LALT (XK_Alt_L&0xff)
#define KEY_CODE_RALT (XK_Alt_R&0xff)

#define KEY_CODE_PAUSE (XK_Pause&0xFF)

#define KEY_CODE_CAPSLOCK (XK_Caps_Lock&0xFF)
#define KEY_CODE_CAPITALLOCK (XK_Caps_Lock&0xFF)

#define KEY_CODE_ESCAPE (XK_Escape&0xFF)
#define KEY_CODE_ESC (XK_Escape&0xFF)

#define KEY_CODE_SPACE (XK_space&0xFF)

#define KEY_CODE_PGUP (XK_Page_Up&0xFF)
#define KEY_CODE_PAGEUP (XK_Page_Down&0xFF)

#define KEY_CODE_PGDN (XK_Page_Down&0xFF)
#define KEY_CODE_PAGEDOWN (XK_Page_Down&0xFF)

#define KEY_CODE_END (XK_End&0xFF)
#define KEY_CODE_HOME (XK_Home&0xFF)

#define KEY_CODE_LEFT (XK_Left&0xFF)
#define KEY_CODE_LEFTARROW (XK_Left&0xFF)

#define KEY_CODE_RIGHT (XK_Right & 0xFF)
#define KEY_CODE_RIGHTARROW (XK_Right&0xFF)

#define KEY_CODE_UP (XK_Up & 0xFF)
#define KEY_CODE_UPARROW (XK_Up&0xFF)

#define KEY_CODE_DOWN (XK_Down & 0xFF)
#define KEY_CODE_DOWNARROW (XK_Down&0xFF)

#define KEY_CODE_SELECT (XK_Select&0xFF)

#define KEY_CODE_EARLYPRINT (XK_Print&0xFF)
#define KEY_CODE_EARLYPRINTSCREEN (XK_Print&0xFF)

#define KEY_CODE_EXECUTE (XK_Execute&0xFF)

#define KEY_CODE_PRINT (XK_Print&0xFF)
#define KEY_CODE_PRINTSCREEN (XK_Print&0xFF)

#define KEY_CODE_INS (XK_Insert&0xFF)
#define KEY_CODE_INSERT (XK_Insert&0xFF)

#define KEY_CODE_DEL (XK_Delete&0xFF)
#define KEY_CODE_DELETE (XK_Delete&0xFF)

#define KEY_CODE_HELP (XK_Help&0xFF)

#define KEY_CODE_0 (XK_0&0xFF)
#define KEY_CODE_1 (XK_1&0xFF)
#define KEY_CODE_2 (XK_2&0xFF)
#define KEY_CODE_3 (XK_3&0xFF)
#define KEY_CODE_4 (XK_4&0xFF)
#define KEY_CODE_5 (XK_5&0xFF)
#define KEY_CODE_6 (XK_6&0xFF)
#define KEY_CODE_7 (XK_7&0xFF)
#define KEY_CODE_8 (XK_8&0xFF)
#define KEY_CODE_9 (XK_9&0xFF)

#define KEY_CODE_A (XK_A&0xFF)
#define KEY_CODE_B (XK_B&0xFF)
#define KEY_CODE_C (XK_C&0xFF)
#define KEY_CODE_D (XK_D&0xFF)
#define KEY_CODE_E (XK_E&0xFF)
#define KEY_CODE_F (XK_F&0xFF)
#define KEY_CODE_G (XK_G&0xFF)
#define KEY_CODE_H (XK_H&0xFF)
#define KEY_CODE_I (XK_I&0xFF)
#define KEY_CODE_J (XK_J&0xFF)
#define KEY_CODE_K (XK_K&0xFF)
#define KEY_CODE_L (XK_L&0xFF)
#define KEY_CODE_M (XK_M&0xFF)
#define KEY_CODE_N (XK_N&0xFF)
#define KEY_CODE_O (XK_O&0xFF)
#define KEY_CODE_P (XK_P&0xFF)
#define KEY_CODE_Q (XK_Q&0xFF)
#define KEY_CODE_R (XK_R&0xFF)
#define KEY_CODE_S (XK_S&0xFF)
#define KEY_CODE_T (XK_T&0xFF)
#define KEY_CODE_U (XK_U&0xFF)
#define KEY_CODE_V (XK_V&0xFF)
#define KEY_CODE_W (XK_W&0xFF)
#define KEY_CODE_X (XK_X&0xFF)
#define KEY_CODE_Y (XK_Y&0xFF)
#define KEY_CODE_Z (XK_Z&0xFF)

#define KEY_CODE_a (XK_a&0xFF)
#define KEY_CODE_b (XK_b&0xFF)
#define KEY_CODE_c (XK_c&0xFF)
#define KEY_CODE_d (XK_d&0xFF)
#define KEY_CODE_e (XK_e&0xFF)
#define KEY_CODE_f (XK_f&0xFF)
#define KEY_CODE_g (XK_g&0xFF)
#define KEY_CODE_h (XK_h&0xFF)
#define KEY_CODE_i (XK_i&0xFF)
#define KEY_CODE_j (XK_j&0xFF)
#define KEY_CODE_k (XK_k&0xFF)
#define KEY_CODE_l (XK_l&0xFF)
#define KEY_CODE_m (XK_m&0xFF)
#define KEY_CODE_n (XK_n&0xFF)
#define KEY_CODE_o (XK_o&0xFF)
#define KEY_CODE_p (XK_p&0xFF)
#define KEY_CODE_q (XK_q&0xFF)
#define KEY_CODE_r (XK_r&0xFF)
#define KEY_CODE_s (XK_s&0xFF)
#define KEY_CODE_t (XK_t&0xFF)
#define KEY_CODE_u (XK_u&0xFF)
#define KEY_CODE_v (XK_v&0xFF)
#define KEY_CODE_w (XK_w&0xFF)
#define KEY_CODE_x (XK_x&0xFF)
#define KEY_CODE_y (XK_y&0xFF)
#define KEY_CODE_z (XK_z&0xFF)


#define KEY_BACKSPACE _KEY(XK_BackSpace&0xFF)
#define KEY_TAB _KEY(XK_Tab&0xFF)

#define KEY_ENTER _KEY(XK_Return&0xFF)
#define KEY_RETURN _KEY(XK_Return&0xFF)

#define KEY_SHIFT	(_KEY(XK_Shift_L&0xff) || _KEY(XK_Shift_R&0xff))
#define KEY_LEFT_SHIFT _KEY(XK_Shift_L&0xff)
#define KEY_RIGHT_SHIFT _KEY(XK_Shift_R&0xff)

#define KEY_CONTROL (_KEY(XK_Control_L&0xff) || _KEY(XK_Control_R&0xff))
#define KEY_LEFT_CONTROL _KEY(XK_Control_L&0xff)
#define KEY_RIGHT_CONTROL _KEY(XK_Control_R&0xff)
#define KEY_CTRL (_KEY(XK_Control_L&0xff) || _KEY(XK_Control_R&0xff))
#define KEY_LCTRL _KEY(XK_Control_L&0xff)
#define KEY_RCTRL _KEY(XK_Control_R&0xff)

#define KEY_ALTERNATIVE (_KEY(XK_Alt_L&0xff) || _KEY(XK_Alt_R&0xff))
#define KEY_LEFT_ALTERNATE _KEY(XK_Alt_L&0xff)
#define KEY_RIGHT_ALTERNATE _KEY(XK_Alt_R&0xff)
#define KEY_ALT (_KEY(XK_Alt_L&0xff) || _KEY(XK_Alt_R&0xff))
#define KEY_LALT _KEY(XK_Alt_L&0xff)
#define KEY_RALT _KEY(XK_Alt_R&0xff)

#define KEY_PAUSE _KEY(XK_Pause&0xFF)

#define KEY_CAPSLOCK _KEY(XK_Caps_Lock&0xFF)
#define KEY_CAPITALLOCK _KEY(XK_Caps_Lock&0xFF)

#define KEY_ESCAPE _KEY(XK_Escape&0xFF)
#define KEY_ESC _KEY(XK_Escape&0xFF)

#define KEY_SPACE _KEY(XK_space&0xFF)

#define KEY_PGUP _KEY(XK_Page_Up&0xFF)
#define KEY_PAGEUP _KEY(XK_Page_Down&0xFF)

#define KEY_PGDN _KEY(XK_Page_Down&0xFF)
#define KEY_PAGEDOWN _KEY(XK_Page_Down&0xFF)

#define KEY_END _KEY(XK_End&0xFF)
#define KEY_HOME _KEY(XK_Home&0xFF)

#define KEY_LEFT _KEY(XK_Left&0xFF)
#define KEY_LEFTARROW _KEY(XK_Left&0xFF)

#define KEY_RIGHT _KEY(XK_Right & 0xFF)
#define KEY_RIGHTARROW _KEY(XK_Right&0xFF)

#define KEY_UP _KEY(XK_Up & 0xFF)
#define KEY_UPARROW _KEY(XK_Up&0xFF)

#define KEY_DOWN _KEY(XK_Down & 0xFF)
#define KEY_DOWNARROW _KEY(XK_Down&0xFF)

#define KEY_SELECT _KEY(XK_Select&0xFF)

#define KEY_EARLYPRINT _KEY(XK_Print&0xFF)
#define KEY_EARLYPRINTSCREEN _KEY(XK_Print&0xFF)

#define KEY_EXECUTE _KEY(XK_Execute&0xFF)

#define KEY_PRINT _KEY(XK_Print&0xFF)
#define KEY_PRINTSCREEN _KEY(XK_Print&0xFF)

#define KEY_INS _KEY(XK_Insert&0xFF)
#define KEY_INSERT _KEY(XK_Insert&0xFF)

#define KEY_DEL _KEY(XK_Delete&0xFF)
#define KEY_DELETE _KEY(XK_Delete&0xFF)

#define KEY_HELP _KEY(XK_Help&0xFF)

#define KEY_0 _KEY(XK_0&0xFF)
#define KEY_1 _KEY(XK_1&0xFF)
#define KEY_2 _KEY(XK_2&0xFF)
#define KEY_3 _KEY(XK_3&0xFF)
#define KEY_4 _KEY(XK_4&0xFF)
#define KEY_5 _KEY(XK_5&0xFF)
#define KEY_6 _KEY(XK_6&0xFF)
#define KEY_7 _KEY(XK_7&0xFF)
#define KEY_8 _KEY(XK_8&0xFF)
#define KEY_9 _KEY(XK_9&0xFF)

#define KEY_A _KEY(XK_A&0xFF)
#define KEY_B _KEY(XK_B&0xFF)
#define KEY_C _KEY(XK_C&0xFF)
#define KEY_D _KEY(XK_D&0xFF)
#define KEY_E _KEY(XK_E&0xFF)
#define KEY_F _KEY(XK_F&0xFF)
#define KEY_G _KEY(XK_G&0xFF)
#define KEY_H _KEY(XK_H&0xFF)
#define KEY_I _KEY(XK_I&0xFF)
#define KEY_J _KEY(XK_J&0xFF)
#define KEY_K _KEY(XK_K&0xFF)
#define KEY_L _KEY(XK_L&0xFF)
#define KEY_M _KEY(XK_M&0xFF)
#define KEY_N _KEY(XK_N&0xFF)
#define KEY_O _KEY(XK_O&0xFF)
#define KEY_P _KEY(XK_P&0xFF)
#define KEY_Q _KEY(XK_Q&0xFF)
#define KEY_R _KEY(XK_R&0xFF)
#define KEY_S _KEY(XK_S&0xFF)
#define KEY_T _KEY(XK_T&0xFF)
#define KEY_U _KEY(XK_U&0xFF)
#define KEY_V _KEY(XK_V&0xFF)
#define KEY_W _KEY(XK_W&0xFF)
#define KEY_X _KEY(XK_X&0xFF)
#define KEY_Y _KEY(XK_Y&0xFF)
#define KEY_Z _KEY(XK_Z&0xFF)

#define KEY_a _KEY(XK_a&0xFF)
#define KEY_b _KEY(XK_b&0xFF)
#define KEY_c _KEY(XK_c&0xFF)
#define KEY_d _KEY(XK_d&0xFF)
#define KEY_e _KEY(XK_e&0xFF)
#define KEY_f _KEY(XK_f&0xFF)
#define KEY_g _KEY(XK_g&0xFF)
#define KEY_h _KEY(XK_h&0xFF)
#define KEY_i _KEY(XK_i&0xFF)
#define KEY_j _KEY(XK_j&0xFF)
#define KEY_k _KEY(XK_k&0xFF)
#define KEY_l _KEY(XK_l&0xFF)
#define KEY_m _KEY(XK_m&0xFF)
#define KEY_n _KEY(XK_n&0xFF)
#define KEY_o _KEY(XK_o&0xFF)
#define KEY_p _KEY(XK_p&0xFF)
#define KEY_q _KEY(XK_q&0xFF)
#define KEY_r _KEY(XK_r&0xFF)
#define KEY_s _KEY(XK_s&0xFF)
#define KEY_t _KEY(XK_t&0xFF)
#define KEY_u _KEY(XK_u&0xFF)
#define KEY_v _KEY(XK_v&0xFF)
#define KEY_w _KEY(XK_w&0xFF)
#define KEY_x _KEY(XK_x&0xFF)
#define KEY_y _KEY(XK_y&0xFF)
#define KEY_z _KEY(XK_z&0xFF)



/* have completed to end of the alphabet (would you believe it) so some keys
   still don't work, however keystore is large enough to take them all */
#endif
