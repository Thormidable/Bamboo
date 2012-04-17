

#if WT_OS_TYPE==OS_WIN32

/* These are the key codes converted from Windows virtual keys. All keys begin
    with KEY_ and end with either the long or short version of the key name  */
#define KEY_CODE_BACKSPACE (VK_BACK)
#define KEY_CODE_TAB (VK_TAB)

#define KEY_CODE_ENTER (VK_RETURN)
#define KEY_CODE_RETURN (VK_RETURN)

#define KEY_CODE_SHIFT (VK_SHIFT)

#define KEY_CODE_CONTROL (VK_CONTROL)
#define KEY_CODE_CTRL (VK_CONTROL)

#define KEY_CODE_ALTERNATE (VK_MENU)
#define KEY_CODE_ALT (VK_MENU)

#define KEY_CODE_PAUSE (VK_PAUSE)

#define KEY_CODE_CAPSLOCK (VK_CAPITAL)
#define KEY_CODE_CAPITALlOCK (VK_CAPITAL)

#define KEY_CODE_ESCAPE (VK_ESCAPE)
#define KEY_CODE_ESC (VK_ESCAPE)

#define KEY_CODE_SPACE (VK_SPACE)

#define KEY_CODE_PGUP (VK_PRIOR)
#define KEY_CODE_PAGEUP (VK_PRIOR)

#define KEY_CODE_PGDN (VK_NEXT)
#define KEY_CODE_PAGEDOWN (VK_NEXT)

#define KEY_CODE_END (VK_END)
#define KEY_CODE_HOME (VK_HOME)

#define KEY_CODE_LEFT (VK_LEFT)
#define KEY_CODE_LEFTARROW (VK_LEFT)

#define KEY_CODE_RIGHT (VK_RIGHT)
#define KEY_CODE_RIGHTARROW (VK_RIGHT)

#define KEY_CODE_UP (VK_UP)
#define KEY_CODE_UPARROW (VK_UP)

#define KEY_CODE_DOWN (VK_DOWN)
#define KEY_CODE_DOWNARROW (VK_DOWN)

#define KEY_CODE_SELECT (VK_SELECT)

#define KEY_CODE_EARLYPRINT (VK_PRINT)
#define KEY_CODE_EARLYPRINTSCREEN (VK_PRINT)

#define KEY_CODE_EXECTUE (VK_EXECUTE)

#define KEY_CODE_PRINT (VK_SNAPSHOT)
#define KEY_CODE_PRINTSCREEN (VK_SNAPSHOT)

#define KEY_CODE_INS (VK_INSERT)
#define KEY_CODE_INSERT (VK_INSERT)

#define KEY_CODE_DEL (VK_DELETE)
#define KEY_CODE_DELETE (VK_DELETE)

#define KEY_CODE_HELP (VK_HELP)


#define KEY_CODE_0 (0x30)
#define KEY_CODE_1 (0x31)
#define KEY_CODE_2 (0x32)
#define KEY_CODE_3 (0x33)
#define KEY_CODE_4 (0x34)
#define KEY_CODE_5 (0x35)
#define KEY_CODE_6 (0x36)
#define KEY_CODE_7 (0x37)
#define KEY_CODE_8 (0x38)
#define KEY_CODE_9 (0x39)

#define KEY_CODE_A (0x41)
#define KEY_CODE_B (0x42)
#define KEY_CODE_C (0x43)
#define KEY_CODE_D (0x44)
#define KEY_CODE_E (0x45)
#define KEY_CODE_F (0x46)
#define KEY_CODE_G (0x47)
#define KEY_CODE_H (0x48)
#define KEY_CODE_I (0x49)
#define KEY_CODE_J (0x4A)
#define KEY_CODE_K (0x4B)
#define KEY_CODE_L (0x4C)
#define KEY_CODE_M (0x4D)
#define KEY_CODE_N (0x4E)
#define KEY_CODE_O (0x4F)
#define KEY_CODE_P (0x50)
#define KEY_CODE_Q (0x51)
#define KEY_CODE_R (0x52)
#define KEY_CODE_S (0x53)
#define KEY_CODE_T (0x54)
#define KEY_CODE_U (0x55)
#define KEY_CODE_V (0x56)
#define KEY_CODE_W (0x57)
#define KEY_CODE_X (0x58)
#define KEY_CODE_Y (0x59)
#define KEY_CODE_Z (0x5A)

#define KEY_CODE_a (0x41)
#define KEY_CODE_b (0x42)
#define KEY_CODE_c (0x43)
#define KEY_CODE_d (0x44)
#define KEY_CODE_e (0x45)
#define KEY_CODE_f (0x46)
#define KEY_CODE_g (0x47)
#define KEY_CODE_h (0x48)
#define KEY_CODE_i (0x49)
#define KEY_CODE_j (0x4A)
#define KEY_CODE_k (0x4B)
#define KEY_CODE_l (0x4C)
#define KEY_CODE_m (0x4D)
#define KEY_CODE_n (0x4E)
#define KEY_CODE_o (0x4F)
#define KEY_CODE_p (0x50)
#define KEY_CODE_q (0x51)
#define KEY_CODE_r (0x52)
#define KEY_CODE_s (0x53)
#define KEY_CODE_t (0x54)
#define KEY_CODE_u (0x55)
#define KEY_CODE_v (0x56)
#define KEY_CODE_w (0x57)
#define KEY_CODE_x (0x58)
#define KEY_CODE_y (0x59)
#define KEY_CODE_z (0x5A)





/* These are the key codes converted from Windows virtual keys. All keys begin
    with KEY_ and end with either the long or short version of the key name  */
#define KEY_BACKSPACE _KEY(VK_BACK)
#define KEY_TAB _KEY(VK_TAB)

#define KEY_ENTER _KEY(VK_RETURN)
#define KEY_RETURN _KEY(VK_RETURN)

#define KEY_SHIFT _KEY(VK_SHIFT)

#define KEY_CONTROL _KEY(VK_CONTROL)
#define KEY_CTRL _KEY(VK_CONTROL)

#define KEY_ALTERNATE _KEY(VK_MENU)
#define KEY_ALT _KEY(VK_MENU)

#define KEY_PAUSE _KEY(VK_PAUSE)

#define KEY_CAPSLOCK _KEY(VK_CAPITAL)
#define KEY_CAPITALlOCK _KEY(VK_CAPITAL)

#define KEY_ESCAPE _KEY(VK_ESCAPE)
#define KEY_ESC _KEY(VK_ESCAPE)

#define KEY_SPACE _KEY(VK_SPACE)

#define KEY_PGUP _KEY(VK_PRIOR)
#define KEY_PAGEUP _KEY(VK_PRIOR)

#define KEY_PGDN _KEY(VK_NEXT)
#define KEY_PAGEDOWN _KEY(VK_NEXT)

#define KEY_END _KEY(VK_END)
#define KEY_HOME _KEY(VK_HOME)

#define KEY_LEFT _KEY(VK_LEFT)
#define KEY_LEFTARROW _KEY(VK_LEFT)

#define KEY_RIGHT _KEY(VK_RIGHT)
#define KEY_RIGHTARROW _KEY(VK_RIGHT)

#define KEY_UP _KEY(VK_UP)
#define KEY_UPARROW _KEY(VK_UP)

#define KEY_DOWN _KEY(VK_DOWN)
#define KEY_DOWNARROW _KEY(VK_DOWN)

#define KEY_SELECT _KEY(VK_SELECT)

#define KEY_EARLYPRINT _KEY(VK_PRINT)
#define KEY_EARLYPRINTSCREEN _KEY(VK_PRINT)

#define KEY_EXECTUE _KEY(VK_EXECUTE)

#define KEY_PRINT _KEY(VK_SNAPSHOT)
#define KEY_PRINTSCREEN _KEY(VK_SNAPSHOT)

#define KEY_INS _KEY(VK_INSERT)
#define KEY_INSERT _KEY(VK_INSERT)

#define KEY_DEL _KEY(VK_DELETE)
#define KEY_DELETE _KEY(VK_DELETE)

#define KEY_HELP _KEY(VK_HELP)


#define KEY_0 _KEY(0x30)
#define KEY_1 _KEY(0x31)
#define KEY_2 _KEY(0x32)
#define KEY_3 _KEY(0x33)
#define KEY_4 _KEY(0x34)
#define KEY_5 _KEY(0x35)
#define KEY_6 _KEY(0x36)
#define KEY_7 _KEY(0x37)
#define KEY_8 _KEY(0x38)
#define KEY_9 _KEY(0x39)

#define KEY_A _KEY(0x41)
#define KEY_B _KEY(0x42)
#define KEY_C _KEY(0x43)
#define KEY_D _KEY(0x44)
#define KEY_E _KEY(0x45)
#define KEY_F _KEY(0x46)
#define KEY_G _KEY(0x47)
#define KEY_H _KEY(0x48)
#define KEY_I _KEY(0x49)
#define KEY_J _KEY(0x4A)
#define KEY_K _KEY(0x4B)
#define KEY_L _KEY(0x4C)
#define KEY_M _KEY(0x4D)
#define KEY_N _KEY(0x4E)
#define KEY_O _KEY(0x4F)
#define KEY_P _KEY(0x50)
#define KEY_Q _KEY(0x51)
#define KEY_R _KEY(0x52)
#define KEY_S _KEY(0x53)
#define KEY_T _KEY(0x54)
#define KEY_U _KEY(0x55)
#define KEY_V _KEY(0x56)
#define KEY_W _KEY(0x57)
#define KEY_X _KEY(0x58)
#define KEY_Y _KEY(0x59)
#define KEY_Z _KEY(0x5A)

#define KEY_a _KEY(0x41)
#define KEY_b _KEY(0x42)
#define KEY_c _KEY(0x43)
#define KEY_d _KEY(0x44)
#define KEY_e _KEY(0x45)
#define KEY_f _KEY(0x46)
#define KEY_g _KEY(0x47)
#define KEY_h _KEY(0x48)
#define KEY_i _KEY(0x49)
#define KEY_j _KEY(0x4A)
#define KEY_k _KEY(0x4B)
#define KEY_l _KEY(0x4C)
#define KEY_m _KEY(0x4D)
#define KEY_n _KEY(0x4E)
#define KEY_o _KEY(0x4F)
#define KEY_p _KEY(0x50)
#define KEY_q _KEY(0x51)
#define KEY_r _KEY(0x52)
#define KEY_s _KEY(0x53)
#define KEY_t _KEY(0x54)
#define KEY_u _KEY(0x55)
#define KEY_v _KEY(0x56)
#define KEY_w _KEY(0x57)
#define KEY_x _KEY(0x58)
#define KEY_y _KEY(0x59)
#define KEY_z _KEY(0x5A)



/* have completed to end of the alphabet (would you believe it) so some keys
   still don't work, however keystore is large enough to take them all */
#endif
