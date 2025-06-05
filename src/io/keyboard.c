#include "keyboard.h"

static const char scancode_to_ascii[128] = {
    /*00*/ 0,
    27,
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    /*08*/ '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\b',
    '\t',
    /*10*/ 'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    /*18*/ 'o',
    'p',
    '[',
    ']',
    '\n',
    0,
    'a',
    's',
    /*20*/ 'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    /*28*/ '\'',
    '`',
    0,
    '\\',
    'z',
    'x',
    'c',
    'v',
    /*30*/ 'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    0,
    '*',
    /*38*/ 0,
    ' ',
    0,
    0,
    0,
    0,
    0,
    0,
    /*40*/ 0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    /*48*/ 0,
    0,
    0,
    0,
    0,
    0,
    0,
    '7', /* keypad (NumLock off) */
    /*50*/ '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    /*58*/ '2',
    '3',
    '0',
    '.',
    0,
    0,
    0,
    0,
};

static const char scancode_to_ascii_shift[128] = {
    /*00*/ 0,
    27,
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    /*08*/ '&',
    '*',
    '(',
    ')',
    '_',
    '+',
    '\b',
    '\t',
    /*10*/ 'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    /*18*/ 'O',
    'P',
    '{',
    '}',
    '\n',
    0,
    'A',
    'S',
    /*20*/ 'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    ':',
    /*28*/ '"',
    '~',
    0,
    '|',
    'Z',
    'X',
    'C',
    'V',
    /*30*/ 'B',
    'N',
    'M',
    '<',
    '>',
    '?',
    0,
    '*',
    /*38*/ 0,
    ' ',
    0,
    0,
    0,
    0,
    0,
    0,
    /*40*/ 0,
    0,
    0,
    0,
    0,
    0,
    0,
    '7',
    /*48*/ '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    /*50*/ '2',
    '3',
    '0',
    '.',
    0,
    0,
    0,
    0,
};

static const struct
{
  uint8_t sc;
  const char *seq;
} esc_keys[] = {
    {0x48, "[A"},  /* Up    */
    {0x50, "[B"},  /* Down  */
    {0x4B, "[D"},  /* Left  */
    {0x4D, "[C"},  /* Right */
    {0x47, "[H"},  /* Home  */
    {0x4F, "[F"},  /* End   */
    {0x49, "[5~"}, /* PgUp  */
    {0x51, "[6~"}, /* PgDn  */
    {0x52, "[2~"}, /* Insert*/
    {0x53, "[3~"}, /* Delete*/
    {0x3B, "[11~"},
    /* F1    */ {0x3C, "[12~"}, /* F2 */
    {0x3D, "[13~"},
    /* F3    */ {0x3E, "[14~"}, /* F4 */
    {0x3F, "[15~"},
    /* F5    */ {0x40, "[17~"}, /* F6 */
    {0x41, "[18~"},
    /* F7    */ {0x42, "[19~"}, /* F8 */
    {0x43, "[20~"},
    /* F9    */ {0x44, "[21~"}, /* F10*/
    {0x57, "[23~"},
    /* F11   */ {0x58, "[24~"}, /* F12*/
};

static bool shift = false;
static bool caps = false;

static inline bool is_alpha(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void handle_keyboard(registers *regs)
{
  (void)regs;

  while ((inb(0x64) & 0x01) == 0)
    ;
  uint8_t sc = inb(0x60);

  if (sc & 0x80)
  {
    sc &= 0x7F;
    if (sc == 0x2A || sc == 0x36) // L/R shift up
    {
      shift = false;
    }

    return;
  }

  switch (sc)
  {
  case 0x2A:
  case 0x36: // L/R shift
    shift = true;
    break;
  case 0x3A: // caps lock
    caps = !caps;
    break;
  default:
  {
    char ch = 0;
    if (sc < 128)
    {
      bool use_shift = shift ^ (caps && (is_alpha(scancode_to_ascii[sc])));
      ch = use_shift ? scancode_to_ascii_shift[sc] : scancode_to_ascii[sc];
    }

    if (ch)
    {
      term_printf("%c", ch);
    }
    else
    {
      for (unsigned i = 0; i < sizeof esc_keys / sizeof esc_keys[0]; i++)
      {
        if (esc_keys[i].sc == sc)
        {
          term_printf("\x1B");
          term_write(esc_keys[i].seq);
          break;
        }
      }
      break;
    }
  }
  }

  pic_send_eoi(1);
}