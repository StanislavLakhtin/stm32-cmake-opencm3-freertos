#ifndef BBB_USDCDC_H
#define BBB_USDCDC_H

#ifdef __cplusplus
extern "C" {
#endif

int usb_ready(void);
void usb_putc(char ch);
int usb_getc(void);

#ifdef __cplusplus
}
#endif

#endif //BBB_USDCDC_H
