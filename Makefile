CC = gcc
CXX = g++
AR = ar rcs

BASE_PATH     := .
LIBDIR        := $(BASE_PATH)/lib

AMRLIB = $(BASE_PATH)/amrlib
AMRAPP = $(BASE_PATH)/amrapp

STATICLIB = $(LIBDIR)/libamr2wav.a 

LIBS = -L$(LIBDIR)/ -lamr2wav

TARGET = $(BASE_PATH)/test/AmrTest.exe

TCSRCS = $(BASE_PATH)/test/AmrApp.c

TESTOBJ = $(BASE_PATH)/test/AmrApp.o

CFLAGS = -O3 -Wall -I$(AMRLIB)/common/include -I$(AMRLIB)/dec/include \
	-I$(AMRLIB)/dec/src -I$(AMRLIB)/enc/include -I$(AMRLIB)/enc/src -I$(AMRLIB)/include \
	-I$(AMRAPP)/

CSRCS = $(AMRAPP)/decode.c $(AMRAPP)/amrfile.c $(AMRAPP)/frmbtord.c\
			$(AMRAPP)/wavefile.c 

CPPSRCS = $(AMRLIB)/amr_if.cpp \
    $(AMRLIB)/common/src/window_tab.cpp \
    $(AMRLIB)/common/src/weight_a.cpp \
    $(AMRLIB)/common/src/vad1.cpp \
    $(AMRLIB)/common/src/syn_filt.cpp \
    $(AMRLIB)/common/src/sub.cpp \
    $(AMRLIB)/common/src/sqrt_l_tbl.cpp \
    $(AMRLIB)/common/src/sqrt_l.cpp \
    $(AMRLIB)/common/src/shr_r.cpp \
    $(AMRLIB)/common/src/shr.cpp \
    $(AMRLIB)/common/src/set_zero.cpp \
    $(AMRLIB)/common/src/round.cpp \
    $(AMRLIB)/common/src/residu.cpp \
    $(AMRLIB)/common/src/reorder.cpp \
    $(AMRLIB)/common/src/qua_gain_tbl.cpp \
    $(AMRLIB)/common/src/q_plsf_5_tbl.cpp \
    $(AMRLIB)/common/src/q_plsf_5.cpp \
    $(AMRLIB)/common/src/q_plsf_3_tbl.cpp \
    $(AMRLIB)/common/src/q_plsf_3.cpp \
    $(AMRLIB)/common/src/q_plsf.cpp \
    $(AMRLIB)/common/src/pred_lt.cpp \
    $(AMRLIB)/common/src/pow2_tbl.cpp \
    $(AMRLIB)/common/src/pow2.cpp \
    $(AMRLIB)/common/src/ph_disp_tab.cpp \
    $(AMRLIB)/common/src/overflow_tbl.cpp \
    $(AMRLIB)/common/src/norm_s.cpp \
    $(AMRLIB)/common/src/norm_l.cpp \
    $(AMRLIB)/common/src/negate.cpp \
    $(AMRLIB)/common/src/mult_r.cpp \
    $(AMRLIB)/common/src/lsp_tab.cpp \
    $(AMRLIB)/common/src/lsp_lsf_tbl.cpp \
    $(AMRLIB)/common/src/lsp_lsf.cpp \
    $(AMRLIB)/common/src/lsp_az.cpp \
    $(AMRLIB)/common/src/lsp.cpp \
    $(AMRLIB)/common/src/lsfwt.cpp \
    $(AMRLIB)/common/src/log2_tbl.cpp \
    $(AMRLIB)/common/src/log2_norm.cpp \
    $(AMRLIB)/common/src/log2.cpp \
    $(AMRLIB)/common/src/l_shr_r.cpp \
    $(AMRLIB)/common/src/l_deposit_l.cpp \
    $(AMRLIB)/common/src/l_deposit_h.cpp \
    $(AMRLIB)/common/src/l_abs.cpp \
    $(AMRLIB)/common/src/inv_sqrt_tbl.cpp \
    $(AMRLIB)/common/src/inv_sqrt.cpp \
    $(AMRLIB)/common/src/int_lpc.cpp \
    $(AMRLIB)/common/src/grid_tbl.cpp \
    $(AMRLIB)/common/src/gray_tbl.cpp \
    $(AMRLIB)/common/src/gmed_n.cpp \
    $(AMRLIB)/common/src/gc_pred.cpp \
    $(AMRLIB)/common/src/gains_tbl.cpp \
    $(AMRLIB)/common/src/extract_l.cpp \
    $(AMRLIB)/common/src/extract_h.cpp \
    $(AMRLIB)/common/src/div_s.cpp \
    $(AMRLIB)/common/src/div_32.cpp \
    $(AMRLIB)/common/src/copy.cpp \
    $(AMRLIB)/common/src/c2_9pf_tab.cpp \
    $(AMRLIB)/common/src/bytesused.cpp \
    $(AMRLIB)/common/src/bits2prm.cpp \
    $(AMRLIB)/common/src/bitreorder_tab.cpp \
    $(AMRLIB)/common/src/bitno_tab.cpp \
    $(AMRLIB)/common/src/az_lsp.cpp \
    $(AMRLIB)/common/src/add.cpp \
    $(AMRLIB)/dec/src/wmf_to_ets.cpp \
    $(AMRLIB)/dec/src/sp_dec.cpp \
    $(AMRLIB)/dec/src/qgain475_tab.cpp \
    $(AMRLIB)/dec/src/pvgsmamrdecoder.cpp \
    $(AMRLIB)/dec/src/pstfilt.cpp \
    $(AMRLIB)/dec/src/preemph.cpp \
    $(AMRLIB)/dec/src/post_pro.cpp \
    $(AMRLIB)/dec/src/ph_disp.cpp \
    $(AMRLIB)/dec/src/lsp_avg.cpp \
    $(AMRLIB)/dec/src/int_lsf.cpp \
    $(AMRLIB)/dec/src/if2_to_ets.cpp \
    $(AMRLIB)/dec/src/ex_ctrl.cpp \
    $(AMRLIB)/dec/src/ec_gains.cpp \
    $(AMRLIB)/dec/src/dtx_dec.cpp \
    $(AMRLIB)/dec/src/decoder_gsm_amr.cpp \
    $(AMRLIB)/dec/src/dec_lag6.cpp \
    $(AMRLIB)/dec/src/dec_lag3.cpp \
    $(AMRLIB)/dec/src/dec_input_format_tab.cpp \
    $(AMRLIB)/dec/src/dec_gain.cpp \
    $(AMRLIB)/dec/src/dec_amr.cpp \
    $(AMRLIB)/dec/src/d_plsf_5.cpp \
    $(AMRLIB)/dec/src/d_plsf_3.cpp \
    $(AMRLIB)/dec/src/d_plsf.cpp \
    $(AMRLIB)/dec/src/d_gain_p.cpp \
    $(AMRLIB)/dec/src/d_gain_c.cpp \
    $(AMRLIB)/dec/src/d1035pf.cpp \
    $(AMRLIB)/dec/src/d8_31pf.cpp \
    $(AMRLIB)/dec/src/d4_17pf.cpp \
    $(AMRLIB)/dec/src/d3_14pf.cpp \
    $(AMRLIB)/dec/src/d2_11pf.cpp \
    $(AMRLIB)/dec/src/d2_9pf.cpp \
    $(AMRLIB)/dec/src/c_g_aver.cpp \
    $(AMRLIB)/dec/src/bgnscd.cpp \
    $(AMRLIB)/dec/src/b_cn_cod.cpp \
    $(AMRLIB)/dec/src/amrdecode.cpp \
    $(AMRLIB)/dec/src/agc.cpp \
    $(AMRLIB)/dec/src/a_refl.cpp \
    $(AMRLIB)/enc/src/ton_stab.cpp \
    $(AMRLIB)/enc/src/spstproc.cpp \
    $(AMRLIB)/enc/src/spreproc.cpp \
    $(AMRLIB)/enc/src/sp_enc.cpp \
    $(AMRLIB)/enc/src/sid_sync.cpp \
    $(AMRLIB)/enc/src/set_sign.cpp \
    $(AMRLIB)/enc/src/s10_8pf.cpp \
    $(AMRLIB)/enc/src/qua_gain.cpp \
    $(AMRLIB)/enc/src/qgain795.cpp \
    $(AMRLIB)/enc/src/qgain475.cpp \
    $(AMRLIB)/enc/src/q_gain_p.cpp \
    $(AMRLIB)/enc/src/q_gain_c.cpp \
    $(AMRLIB)/enc/src/prm2bits.cpp \
    $(AMRLIB)/enc/src/pre_proc.cpp \
    $(AMRLIB)/enc/src/pre_big.cpp \
    $(AMRLIB)/enc/src/pitch_ol.cpp \
    $(AMRLIB)/enc/src/pitch_fr.cpp \
    $(AMRLIB)/enc/src/p_ol_wgh.cpp \
    $(AMRLIB)/enc/src/ol_ltp.cpp \
    $(AMRLIB)/enc/src/lpc.cpp \
    $(AMRLIB)/enc/src/levinson.cpp \
    $(AMRLIB)/enc/src/lag_wind_tab.cpp \
    $(AMRLIB)/enc/src/lag_wind.cpp \
    $(AMRLIB)/enc/src/l_negate.cpp \
    $(AMRLIB)/enc/src/l_extract.cpp \
    $(AMRLIB)/enc/src/l_comp.cpp \
    $(AMRLIB)/enc/src/inter_36_tab.cpp \
    $(AMRLIB)/enc/src/inter_36.cpp \
    $(AMRLIB)/enc/src/hp_max.cpp \
    $(AMRLIB)/enc/src/gsmamr_encoder_wrapper.cpp \
    $(AMRLIB)/enc/src/gain_q.cpp \
    $(AMRLIB)/enc/src/g_pitch.cpp \
    $(AMRLIB)/enc/src/g_code.cpp \
    $(AMRLIB)/enc/src/g_adapt.cpp \
    $(AMRLIB)/enc/src/ets_to_wmf.cpp \
    $(AMRLIB)/enc/src/ets_to_if2.cpp \
    $(AMRLIB)/enc/src/enc_output_format_tab.cpp \
    $(AMRLIB)/enc/src/enc_lag6.cpp \
    $(AMRLIB)/enc/src/enc_lag3.cpp \
    $(AMRLIB)/enc/src/dtx_enc.cpp \
    $(AMRLIB)/enc/src/corrwght_tab.cpp \
    $(AMRLIB)/enc/src/cor_h_x.cpp \
    $(AMRLIB)/enc/src/cor_h_x2.cpp \
    $(AMRLIB)/enc/src/cor_h.cpp \
    $(AMRLIB)/enc/src/convolve.cpp \
    $(AMRLIB)/enc/src/cod_amr.cpp \
    $(AMRLIB)/enc/src/cl_ltp.cpp \
    $(AMRLIB)/enc/src/cbsearch.cpp \
    $(AMRLIB)/enc/src/calc_en.cpp \
    $(AMRLIB)/enc/src/calc_cor.cpp \
    $(AMRLIB)/enc/src/c1035pf.cpp \
    $(AMRLIB)/enc/src/c8_31pf.cpp \
    $(AMRLIB)/enc/src/c4_17pf.cpp \
    $(AMRLIB)/enc/src/c3_14pf.cpp \
    $(AMRLIB)/enc/src/c2_11pf.cpp \
    $(AMRLIB)/enc/src/c2_9pf.cpp \
    $(AMRLIB)/enc/src/autocorr.cpp \
    $(AMRLIB)/enc/src/amrencode.cpp

OBJS = $(CSRCS:.c=.o) $(CPPSRCS:.cpp=.o)

all:	 $(TESTOBJ) $(TARGET)
$(TARGET):$(OBJS)
	$(AR) $(STATICLIB) $(OBJS)
	$(CXX) -o $(TARGET)  $(OBJS) $(TESTOBJ)

$(TESTOBJ): $(TCSRCS)
	$(CC) -c -o $@ $(CFLAGS) $^

%.o: %.cpp
	$(CXX) -c -o $@ $(CFLAGS) $^

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $^


clean:
	@rm -f $(OBJS) $(TARGET) $(STATICLIB) $(TESTOBJ)
