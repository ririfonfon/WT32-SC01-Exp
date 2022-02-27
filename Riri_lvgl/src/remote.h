#ifndef remote_h
#define remote_h

#include "lvgl.h"

// /*********************
//  *      DEFINES
//  *********************/

// /**********************
//  *      TYPEDEFS
//  **********************/

// /**********************
//  *  STATIC PROTOTYPES
//  **********************/
static void remote_create(lv_obj_t *parent);
static void text_area_event_handler(lv_obj_t *text_area, lv_event_t event);
static void keyboard_event_cb(lv_obj_t *keyboard, lv_event_t event);
static void keyboard_create(lv_obj_t *parent);

#if LV_USE_ANIMATION
static void kb_hide_anim_end(lv_anim_t *a);
#endif

static void option_create(lv_obj_t *parent);
static void output_create(lv_obj_t *parent);
static void slider_event_handler(lv_obj_t *slider, lv_event_t event);
static void list_btn_event_handler(lv_obj_t *slider, lv_event_t event);

// /**********************
//  *  STATIC VARIABLES
//  **********************/
static lv_obj_t *chart;
static lv_obj_t *ta;
static lv_obj_t *kb;
static lv_obj_t *tv;
static lv_obj_t *tat;

static lv_style_t style_kb;

// /**********************
//  *      MACROS
//  **********************/

// /**********************
//  *   GLOBAL FUNCTIONS
//  **********************/

void getAction(char *action)
{
    lv_keyboard_get_lastTxt(kb, action);
}

/**
 * Create a remote application
 */

void menu_create(void)
{
    lv_coord_t hres = lv_disp_get_hor_res(NULL);
    lv_coord_t vres = lv_disp_get_ver_res(NULL);

    static lv_style_t style_tv_btn;
    lv_style_init(&style_tv_btn);
    lv_style_set_bg_opa(&style_tv_btn, LV_STATE_DEFAULT, LV_OPA_70);
    lv_style_set_bg_color(&style_tv_btn, LV_STATE_DEFAULT, lv_color_hex3(0x333));
    lv_style_set_bg_grad_color(&style_tv_btn, LV_STATE_DEFAULT, lv_color_hex3(0x333));

    lv_style_set_pad_top(&style_tv_btn, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_bottom(&style_tv_btn, LV_STATE_DEFAULT, 20);
    lv_style_set_bg_opa(&style_tv_btn, LV_BTN_STATE_RELEASED, LV_OPA_70);
    lv_style_set_border_width(&style_tv_btn, LV_BTN_STATE_RELEASED, 0);
    lv_style_set_radius(&style_tv_btn, LV_BTN_STATE_PRESSED, 0);
    lv_style_set_bg_opa(&style_tv_btn, LV_BTN_STATE_PRESSED, LV_OPA_70);
    lv_style_set_bg_color(&style_tv_btn, LV_BTN_STATE_PRESSED, LV_COLOR_BLACK); // couleur colone selectionné
    lv_style_set_bg_grad_color(&style_tv_btn, LV_BTN_STATE_PRESSED, LV_COLOR_RED);
    lv_style_set_border_width(&style_tv_btn, LV_BTN_STATE_PRESSED, 0);
    lv_style_set_text_color(&style_tv_btn, LV_BTN_STATE_PRESSED, LV_COLOR_WHITE);

    tv = lv_tabview_create(lv_scr_act(), NULL);

    lv_obj_set_size(tv, hres, vres);

    lv_obj_t *tab1 = lv_tabview_add_tab(tv, "Remote");
    lv_obj_t *tab2 = lv_tabview_add_tab(tv, "Output");

    lv_obj_add_style(tv, LV_TABVIEW_PART_TAB_BTN, &style_tv_btn);

    remote_create(tab1);
    output_create(tab2);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void remote_create(lv_obj_t *parent)
{
    // lv_page_set_style(parent, LV_PAGE_STYLE_BG, &lv_style_transp_fit);
    // lv_page_set_style(parent, LV_PAGE_STYLE_SCRL, &lv_style_transp_fit);

    lv_page_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);

    static lv_style_t style_ta;
    lv_style_init(&style_ta);
    lv_style_set_bg_opa(&style_ta, LV_STATE_DEFAULT, LV_OPA_70);
    lv_style_set_bg_color(&style_ta, LV_STATE_DEFAULT, lv_color_hex3(0x333));
    lv_style_set_bg_grad_color(&style_ta, LV_STATE_DEFAULT, lv_color_hex3(0x333));
    lv_style_set_radius(&style_ta, LV_STATE_DEFAULT, 0);
    lv_style_set_text_color(&style_ta, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_color(&style_ta, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_style_set_text_font(&style_ta, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    ta = lv_textarea_create(parent, NULL);

    lv_obj_set_size(ta, lv_page_get_scrl_width(parent), lv_obj_get_height(parent) / 6 * 1);
    lv_obj_add_style(ta, LV_TEXTAREA_PART_BG, &style_ta);
    lv_textarea_set_text(ta, "");
    lv_obj_set_event_cb(ta, text_area_event_handler);
    lv_textarea_set_text_sel(ta, true);

    lv_style_init(&style_kb);
    lv_style_set_bg_opa(&style_kb, LV_STATE_DEFAULT, LV_OPA_70);
    lv_style_set_bg_color(&style_kb, LV_STATE_DEFAULT, lv_color_hex3(0x333));
    lv_style_set_bg_grad_color(&style_kb, LV_STATE_DEFAULT, lv_color_hex3(0x333));
    lv_style_set_pad_left(&style_kb, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_right(&style_kb, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_top(&style_kb, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_bottom(&style_kb, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_inner(&style_kb, LV_STATE_DEFAULT, 0);

    lv_style_set_bg_opa(&style_kb, LV_BTN_STATE_RELEASED, LV_OPA_70);
    lv_style_set_radius(&style_kb, LV_BTN_STATE_RELEASED, 0);
    lv_style_set_border_width(&style_kb, LV_BTN_STATE_RELEASED, 1);
    lv_style_set_border_color(&style_kb, LV_BTN_STATE_RELEASED, LV_COLOR_SILVER);
    lv_style_set_border_opa(&style_kb, LV_BTN_STATE_RELEASED, LV_OPA_50);
    lv_style_set_bg_color(&style_kb, LV_BTN_STATE_RELEASED, lv_color_hex3(0x333));
    lv_style_set_bg_grad_color(&style_kb, LV_BTN_STATE_RELEASED, lv_color_hex3(0x333));
    lv_style_set_text_color(&style_kb, LV_BTN_STATE_RELEASED, LV_COLOR_WHITE);
    lv_style_set_text_font(&style_kb, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    lv_style_set_radius(&style_kb, LV_BTN_STATE_PRESSED, 0);
    lv_style_set_bg_opa(&style_kb, LV_BTN_STATE_PRESSED, LV_OPA_50);
    lv_style_set_bg_color(&style_kb, LV_BTN_STATE_PRESSED, LV_COLOR_WHITE);
    lv_style_set_bg_grad_color(&style_kb, LV_BTN_STATE_PRESSED, LV_COLOR_WHITE);
    lv_style_set_border_width(&style_kb, LV_BTN_STATE_PRESSED, 1);
    lv_style_set_border_color(&style_kb, LV_BTN_STATE_PRESSED, LV_COLOR_SILVER);

    keyboard_create(parent);
}

static void keyboard_create(lv_obj_t *parent)
{
    if (kb == NULL)
    {
        kb = lv_keyboard_create(parent, NULL);
        lv_obj_set_size(kb, lv_obj_get_width_fit(parent), lv_obj_get_height_fit(parent) / 6 * 5);
        lv_obj_align(kb, ta, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_add_style(kb, LV_KEYBOARD_PART_BG, &style_kb);
        lv_obj_add_style(kb, LV_KEYBOARD_PART_BTN, &style_kb);
        lv_obj_set_event_cb(kb, keyboard_event_cb);

        lv_keyboard_set_mode(kb, 5);

        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, kb);
        lv_anim_set_time(&a, 300);
        lv_anim_set_values(&a, LV_VER_RES, lv_obj_get_y(kb));
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_ready_cb(&a, NULL);
        lv_anim_start(&a);
    }
}

static void text_area_event_handler(lv_obj_t *text_area, lv_event_t event)
{
    (void)text_area; /*Unused*/

    /*Text area is on the scrollable part of the page but we need the page itself*/
    lv_obj_t *parent = lv_obj_get_parent(lv_obj_get_parent(ta));

    keyboard_create(parent);
}

/**
 * Called when the close or ok button is pressed on the keyboard
 * @param keyboard pointer to the keyboard
 * @return
 */
static void keyboard_event_cb(lv_obj_t *keyboard, lv_event_t event)
{
    (void)keyboard; /*Unused*/

    lv_keyboard_def_event_cb(kb, event);

    if (event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL)
    {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, kb);
        lv_anim_set_time(&a, 300);
        lv_anim_set_values(&a, LV_VER_RES, lv_obj_get_y(kb));
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_ready_cb(&a, NULL);
        lv_anim_start(&a);
    }
}

static void output_create(lv_obj_t *parent)
{
    static lv_style_t style_tat;
    lv_style_init(&style_tat);
    lv_style_set_bg_opa(&style_tat, LV_STATE_DEFAULT, LV_OPA_70);
    lv_style_set_bg_color(&style_tat, LV_STATE_DEFAULT, lv_color_hex3(0x333));
    lv_style_set_bg_grad_color(&style_tat, LV_STATE_DEFAULT, lv_color_hex3(0x333));
    lv_style_set_radius(&style_tat, LV_STATE_DEFAULT, 0);
    lv_style_set_text_color(&style_tat, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_color(&style_tat, LV_STATE_FOCUSED, LV_COLOR_WHITE);
    lv_style_set_text_font(&style_tat, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    tat = lv_textarea_create(parent, NULL);

    lv_obj_set_size(tat, lv_page_get_scrl_width(parent), lv_obj_get_height(parent));
    lv_obj_add_style(tat, LV_TEXTAREA_PART_BG, &style_tat);
    lv_textarea_set_text(tat, "");
    lv_obj_set_event_cb(tat, text_area_event_handler);
    lv_textarea_set_text_sel(tat, true);
}
/**
 * Called when a new value on the slider on the Chart tab is set
 * @param slider pointer to the slider
 * @return LV_RES_OK because the slider is not deleted in the function
 */
static void slider_event_handler(lv_obj_t *slider, lv_event_t event)
{

    if (event == LV_EVENT_VALUE_CHANGED)
    {
        int16_t v = lv_slider_get_value(slider);
        v = 1000 * 100 / v; /*Convert to range modify values linearly*/
        lv_chart_set_range(chart, 0, v);
    }
}

/**
 * Called when a a list button is clicked on the List tab
 * @param btn pointer to a list button
 * @return LV_RES_OK because the button is not deleted in the function
 */
static void list_btn_event_handler(lv_obj_t *btn, lv_event_t event)
{

    if (event == LV_EVENT_SHORT_CLICKED)
    {
        lv_textarea_add_char(ta, '\n');
        lv_textarea_add_text(ta, lv_list_get_btn_text(btn));
    }
}

#endif