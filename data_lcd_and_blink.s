; Use LCD on BF80 and 65c22 on BF90 to display text and blink
; LEDs. Use 555 clock input on PA0 as timer for DELAY

LCD = $BF80
LCD0 = $BF80
LCD1 = $BF81
PORTB = $BF90
PORTA = $BF91
DDRB = $BF92
DDRA = $BF93

  .org $8000
  
  .org $C000

reset:
  ldx #$ff	; Setup stack pointer
  txs

  jsr lint
  jsr LCDSTRING  

  lda #$ff
  sta DDRB

  lda #%10101010
  sta PORTB
loop:
  ror
  sta PORTB
  jsr DELAY
  jmp loop


message: .asciiz "BF80 Lights!!!"

lcd2busy:
  pha
lcd2wait:
  lda LCD0
  and #$80
  bne lcd2wait
  pla
  rts
  
lint:
  lda #$38
  sta LCD0
  jsr lcd2busy
  
  lda #$06
  sta LCD0
  jsr lcd2busy
  
  lda #$0E
  sta LCD0
  jsr lcd2busy
  
  lda #$01
  sta LCD0
  jsr lcd2busy
  
  lda #$80
  sta LCD0
  jsr lcd2busy
  rts

LCDPRINT:
  pha
  sta LCD1
  jsr lcd2busy
  lda LCD0
  and #$7F
  cmp #$14
  bne LCDPRINT0
  lda #$C0
  sta LCD0
  jsr lcd2busy
LCDPRINT0:
  pla
  rts
  
LCDSTRING:
  pha
  tya
  ldy #$00
LCDSTR0
  lda message,y
  beq LCDSTR1
  jsr LCDPRINT
  iny
  bne LCDSTR0
LCDSTR1:
  ;pla
  ;tay
  pla
  rts

DELAY:
  pha
wait_on:
  lda PORTA
  and #%00000001
  bne wait_on
wait_off:
  lda PORTA
  and #%00000001
  beq wait_off
  pla
  rts
  
  .org $fffc
  .word reset
  .word $0000
