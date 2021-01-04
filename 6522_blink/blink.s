  .org $8000
  .org $C000
  
reset:
  lda #$ff
  sta $BF92

  lda #$55
  sta $BF90

loop:
  ror
  sta $BF90

  jmp loop

  .org $fffc
  .word reset
  .word $0000
