/* -*- c++ -*- */
/* 
 * Copyright 2015,2016 Free Software Foundation, Inc.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "dvb_bch_bb_impl.h"

namespace gr {
  namespace dtv {

    dvb_bch_bb::sptr
    dvb_bch_bb::make(dvb_standard_t standard, dvb_framesize_t framesize, dvb_code_rate_t rate)
    {
      return gnuradio::get_initial_sptr
        (new dvb_bch_bb_impl(standard, framesize, rate));
    }

    /*
     * The private constructor
     */
    dvb_bch_bb_impl::dvb_bch_bb_impl(dvb_standard_t standard, dvb_framesize_t framesize, dvb_code_rate_t rate)
      : gr::block("dvb_bch_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      if (framesize == FECFRAME_NORMAL) {
        switch (rate) {
          case C1_2:
            kbch = 32208;
            nbch = 32400;
            bch_code = BCH_CODE_N12;
            break;
          case C3_5:
            kbch = 38688;
            nbch = 38880;
            bch_code = BCH_CODE_N12;
            break;
          case C2_3:
            kbch = 43040;
            nbch = 43200;
            bch_code = BCH_CODE_N10;
            break;
          case C3_4:
            kbch = 48408;
            nbch = 48600;
            bch_code = BCH_CODE_N12;
            break;
          case C4_5:
            kbch = 51648;
            nbch = 51840;
            bch_code = BCH_CODE_N12;
            break;
          case C5_6:
            kbch = 53840;
            nbch = 54000;
            bch_code = BCH_CODE_N10;
            break;
          default:
            kbch = 0;
            nbch = 0;
            bch_code = 0;
            break;
        }
      }
      else if (framesize == FECFRAME_SHORT) {
        switch (rate) {
          case C1_4:
            kbch = 3072;
            nbch = 3240;
            bch_code = BCH_CODE_S12;
            break;
          case C1_2:
            kbch = 7032;
            nbch = 7200;
            bch_code = BCH_CODE_S12;
            break;
          case C3_5:
            kbch = 9552;
            nbch = 9720;
            bch_code = BCH_CODE_S12;
            break;
          case C2_3:
            kbch = 10632;
            nbch = 10800;
            bch_code = BCH_CODE_S12;
            break;
          case C3_4:
            kbch = 11712;
            nbch = 11880;
            bch_code = BCH_CODE_S12;
            break;
          case C4_5:
            kbch = 12432;
            nbch = 12600;
            bch_code = BCH_CODE_S12;
            break;
          case C5_6:
            kbch = 13152;
            nbch = 13320;
            bch_code = BCH_CODE_S12;
            break;
          default:
            kbch = 0;
            nbch = 0;
            bch_code = 0;
            break;
        }
      }
      else {
        switch (rate) {
          case C1_5_MEDIUM:
            kbch = 5660;
            nbch = 5840;
            bch_code = BCH_CODE_M12;
            break;
          case C11_45_MEDIUM:
            kbch = 7740;
            nbch = 7920;
            bch_code = BCH_CODE_M12;
            break;
          case C1_3_MEDIUM:
            kbch = 10620;
            nbch = 10800;
            bch_code = BCH_CODE_M12;
            break;
          default:
            kbch = 0;
            nbch = 0;
            bch_code = 0;
            break;
        }
      }

      bch_poly_build_tables();
      set_output_multiple(nbch);
    }

    /*
     * Our virtual destructor.
     */
    dvb_bch_bb_impl::~dvb_bch_bb_impl()
    {
    }

    void
    dvb_bch_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (noutput_items / nbch) * kbch;
    }

    /*
     * Polynomial calculation routines
     * multiply polynomials
     */
    int
    dvb_bch_bb_impl::poly_mult(const int *ina, int lena, const int *inb, int lenb, int *out)
    {
      memset(out, 0, sizeof(int) * (lena + lenb));

      for (int i = 0; i < lena; i++) {
        for (int j = 0; j < lenb; j++) {
          if (ina[i] * inb[j] > 0 ) {
            out[i + j]++;    // count number of terms for this pwr of x
          }
        }
      }
      int max = 0;
      for (int i = 0; i < lena + lenb; i++) {
        out[i] = out[i] & 1;    // If even ignore the term
        if(out[i]) {
          max = i;
        }
      }
      // return the size of array to house the result.
      return max + 1;
    }

    /*
     * Pack the polynomial into a 32 bit array
     */
    void
    dvb_bch_bb_impl::poly_pack(const int *pin, unsigned int* pout, int len)
    {
      int lw = len / 32;
      int ptr = 0;
      unsigned int temp;
      if (len % 32) {
        lw++;
      }

      for (int i = 0; i < lw; i++) {
        temp = 0x80000000;
        pout[i] = 0;
        for (int j = 0; j < 32; j++) {
          if (pin[ptr++]) {
            pout[i] |= temp;
          }
          temp >>= 1;
        }
      }
    }

    void
    dvb_bch_bb_impl::poly_reverse(int *pin, int *pout, int len)
    {
      int c;
      c = len - 1;

      for (int i = 0; i < len; i++) {
        pout[c--] = pin[i];
      }
    }

    /*
     *Shift a 128 bit register
     */
    inline void
    dvb_bch_bb_impl::reg_4_shift(unsigned int *sr)
    {
      sr[3] = (sr[3] >> 1) | (sr[2] << 31);
      sr[2] = (sr[2] >> 1) | (sr[1] << 31);
      sr[1] = (sr[1] >> 1) | (sr[0] << 31);
      sr[0] = (sr[0] >> 1);
    }

    /*
     * Shift 160 bits
     */
    inline void
    dvb_bch_bb_impl::reg_5_shift(unsigned int *sr)
    {
      sr[4] = (sr[4] >> 1) | (sr[3] << 31);
      sr[3] = (sr[3] >> 1) | (sr[2] << 31);
      sr[2] = (sr[2] >> 1) | (sr[1] << 31);
      sr[1] = (sr[1] >> 1) | (sr[0] << 31);
      sr[0] = (sr[0] >> 1);
    }

    /*
     * Shift 192 bits
     */
    inline void
    dvb_bch_bb_impl::reg_6_shift(unsigned int *sr)
    {
      sr[5] = (sr[5] >> 1) | (sr[4] << 31);
      sr[4] = (sr[4] >> 1) | (sr[3] << 31);
      sr[3] = (sr[3] >> 1) | (sr[2] << 31);
      sr[2] = (sr[2] >> 1) | (sr[1] << 31);
      sr[1] = (sr[1] >> 1) | (sr[0] << 31);
      sr[0] = (sr[0] >> 1);
    }

    void
    dvb_bch_bb_impl::bch_poly_build_tables(void)
    {
      // Normal polynomials
      const int polyn01[]={1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1};
      const int polyn02[]={1,1,0,0,1,1,1,0,1,0,0,0,0,0,0,0,1};
      const int polyn03[]={1,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,1};
      const int polyn04[]={1,0,1,0,1,0,1,0,0,1,0,1,1,0,1,0,1};
      const int polyn05[]={1,1,1,1,0,1,0,0,1,1,1,1,1,0,0,0,1};
      const int polyn06[]={1,0,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1};
      const int polyn07[]={1,0,1,0,0,1,1,0,1,1,1,1,0,1,0,1,1};
      const int polyn08[]={1,1,1,0,0,1,1,0,1,1,0,0,1,1,1,0,1};
      const int polyn09[]={1,0,0,0,0,1,0,1,0,1,1,1,0,0,0,0,1};
      const int polyn10[]={1,1,1,0,0,1,0,1,1,0,1,0,1,1,1,0,1};
      const int polyn11[]={1,0,1,1,0,1,0,0,0,1,0,1,1,1,0,0,1};
      const int polyn12[]={1,1,0,0,0,1,1,1,0,1,0,1,1,0,0,0,1};

      // Medium polynomials
      const int polym01[]={1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,1};
      const int polym02[]={1,1,0,0,1,0,0,1,0,0,1,1,0,0,0,1};
      const int polym03[]={1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1};
      const int polym04[]={1,0,1,1,0,1,1,0,1,0,1,1,0,0,0,1};
      const int polym05[]={1,1,1,0,1,0,1,1,0,0,1,0,1,0,0,1};
      const int polym06[]={1,0,0,0,1,0,1,1,0,0,0,0,1,1,0,1};
      const int polym07[]={1,0,1,0,1,1,0,1,0,0,0,1,1,0,1,1};
      const int polym08[]={1,0,1,0,1,0,1,0,1,1,0,1,0,0,1,1};
      const int polym09[]={1,1,1,0,1,1,0,1,0,1,0,1,1,1,0,1};
      const int polym10[]={1,1,1,1,1,0,0,1,0,0,1,1,1,1,0,1};
      const int polym11[]={1,1,1,0,1,0,0,0,0,1,0,1,0,0,0,1};
      const int polym12[]={1,0,1,0,1,0,0,0,1,0,1,1,0,1,1,1};

      // Short polynomials
      const int polys01[]={1,1,0,1,0,1,0,0,0,0,0,0,0,0,1};
      const int polys02[]={1,0,0,0,0,0,1,0,1,0,0,1,0,0,1};
      const int polys03[]={1,1,1,0,0,0,1,0,0,1,1,0,0,0,1};
      const int polys04[]={1,0,0,0,1,0,0,1,1,0,1,0,1,0,1};
      const int polys05[]={1,0,1,0,1,0,1,0,1,1,0,1,0,1,1};
      const int polys06[]={1,0,0,1,0,0,0,1,1,1,0,0,0,1,1};
      const int polys07[]={1,0,1,0,0,1,1,1,0,0,1,1,0,1,1};
      const int polys08[]={1,0,0,0,0,1,0,0,1,1,1,1,0,0,1};
      const int polys09[]={1,1,1,1,0,0,0,0,0,1,1,0,0,0,1};
      const int polys10[]={1,0,0,1,0,0,1,0,0,1,0,1,1,0,1};
      const int polys11[]={1,0,0,0,1,0,0,0,0,0,0,1,1,0,1};
      const int polys12[]={1,1,1,1,0,1,1,1,1,0,1,0,0,1,1};

      int len;
      int polyout[2][200];

      len = poly_mult(polyn01, 17, polyn02,    17,  polyout[0]);
      len = poly_mult(polyn03, 17, polyout[0], len, polyout[1]);
      len = poly_mult(polyn04, 17, polyout[1], len, polyout[0]);
      len = poly_mult(polyn05, 17, polyout[0], len, polyout[1]);
      len = poly_mult(polyn06, 17, polyout[1], len, polyout[0]);
      len = poly_mult(polyn07, 17, polyout[0], len, polyout[1]);
      len = poly_mult(polyn08, 17, polyout[1], len, polyout[0]);
      poly_pack(polyout[0], m_poly_n_8, 128);

      len = poly_mult(polyn09, 17, polyout[0], len, polyout[1]);
      len = poly_mult(polyn10, 17, polyout[1], len, polyout[0]);
      poly_pack(polyout[0], m_poly_n_10, 160);

      len = poly_mult(polyn11, 17, polyout[0], len, polyout[1]);
      len = poly_mult(polyn12, 17, polyout[1], len, polyout[0]);
      poly_pack(polyout[0], m_poly_n_12, 192);

      len = poly_mult(polys01, 15, polys02,    15,  polyout[0]);
      len = poly_mult(polys03, 15, polyout[0], len, polyout[1]);
      len = poly_mult(polys04, 15, polyout[1], len, polyout[0]);
      len = poly_mult(polys05, 15, polyout[0], len, polyout[1]);
      len = poly_mult(polys06, 15, polyout[1], len, polyout[0]);
      len = poly_mult(polys07, 15, polyout[0], len, polyout[1]);
      len = poly_mult(polys08, 15, polyout[1], len, polyout[0]);
      len = poly_mult(polys09, 15, polyout[0], len, polyout[1]);
      len = poly_mult(polys10, 15, polyout[1], len, polyout[0]);
      len = poly_mult(polys11, 15, polyout[0], len, polyout[1]);
      len = poly_mult(polys12, 15, polyout[1], len, polyout[0]);
      poly_pack(polyout[0], m_poly_s_12, 168);

      len = poly_mult(polym01, 16, polym02,    16,  polyout[0]);
      len = poly_mult(polym03, 16, polyout[0], len, polyout[1]);
      len = poly_mult(polym04, 16, polyout[1], len, polyout[0]);
      len = poly_mult(polym05, 16, polyout[0], len, polyout[1]);
      len = poly_mult(polym06, 16, polyout[1], len, polyout[0]);
      len = poly_mult(polym07, 16, polyout[0], len, polyout[1]);
      len = poly_mult(polym08, 16, polyout[1], len, polyout[0]);
      len = poly_mult(polym09, 16, polyout[0], len, polyout[1]);
      len = poly_mult(polym10, 16, polyout[1], len, polyout[0]);
      len = poly_mult(polym11, 16, polyout[0], len, polyout[1]);
      len = poly_mult(polym12, 16, polyout[1], len, polyout[0]);
      poly_pack(polyout[0], m_poly_m_12, 180);
    }

    int
    dvb_bch_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      unsigned char b, temp;
      unsigned int shift[6];
      int consumed = 0;

      switch (bch_code) {
        case BCH_CODE_N12:
          for (int i = 0; i < noutput_items; i += nbch) {
            //Zero the shift register
            memset(shift, 0, sizeof(unsigned int) * 6);
            // MSB of the codeword first
            for (int j = 0; j < (int)kbch; j++) {
              temp = *in++;
              *out++ = temp;
              consumed++;
              b = (temp ^ (shift[5] & 1));
              reg_6_shift(shift);
              if (b) {
                shift[0] ^= m_poly_n_12[0];
                shift[1] ^= m_poly_n_12[1];
                shift[2] ^= m_poly_n_12[2];
                shift[3] ^= m_poly_n_12[3];
                shift[4] ^= m_poly_n_12[4];
                shift[5] ^= m_poly_n_12[5];
              }
            }
            // Now add the parity bits to the output
            for (int n = 0; n < 192; n++) {
              *out++ = (shift[5] & 1);
              reg_6_shift(shift);
            }
          }
          break;
        case BCH_CODE_N10:
          for (int i = 0; i < noutput_items; i += nbch) {
            //Zero the shift register
            memset(shift, 0, sizeof(unsigned int) * 5);
            // MSB of the codeword first
            for (int j = 0; j < (int)kbch; j++) {
              temp = *in++;
              *out++ = temp;
              consumed++;
              b = (temp ^ (shift[4] & 1));
              reg_5_shift(shift);
              if (b) {
                shift[0] ^= m_poly_n_10[0];
                shift[1] ^= m_poly_n_10[1];
                shift[2] ^= m_poly_n_10[2];
                shift[3] ^= m_poly_n_10[3];
                shift[4] ^= m_poly_n_10[4];
              }
            }
            // Now add the parity bits to the output
            for( int n = 0; n < 160; n++ ) {
              *out++ = (shift[4] & 1);
              reg_5_shift(shift);
            }
          }
          break;
        case BCH_CODE_N8:
          for (int i = 0; i < noutput_items; i += nbch) {
            //Zero the shift register
            memset(shift, 0, sizeof(unsigned int) * 4);
            // MSB of the codeword first
            for (int j = 0; j < (int)kbch; j++) {
              temp = *in++;
              *out++ = temp;
              consumed++;
              b = temp ^ (shift[3] & 1);
              reg_4_shift(shift);
              if (b) {
                shift[0] ^= m_poly_n_8[0];
                shift[1] ^= m_poly_n_8[1];
                shift[2] ^= m_poly_n_8[2];
                shift[3] ^= m_poly_n_8[3];
              }
            }
            // Now add the parity bits to the output
            for (int n = 0; n < 128; n++) {
              *out++ = shift[3] & 1;
              reg_4_shift(shift);
            }
          }
          break;
        case BCH_CODE_S12:
          for (int i = 0; i < noutput_items; i += nbch) {
            //Zero the shift register
            memset(shift, 0, sizeof(unsigned int) * 6);
            // MSB of the codeword first
            for (int j = 0; j < (int)kbch; j++) {
              temp = *in++;
              *out++ = temp;
              consumed++;
              b = (temp ^ ((shift[5] & 0x01000000) ? 1 : 0));
              reg_6_shift(shift);
              if (b) {
                shift[0] ^= m_poly_s_12[0];
                shift[1] ^= m_poly_s_12[1];
                shift[2] ^= m_poly_s_12[2];
                shift[3] ^= m_poly_s_12[3];
                shift[4] ^= m_poly_s_12[4];
                shift[5] ^= m_poly_s_12[5];
              }
            }
            // Now add the parity bits to the output
            for (int n = 0; n < 168; n++) {
              *out++ = (shift[5] & 0x01000000) ? 1 : 0;
              reg_6_shift(shift);
            }
          }
          break;
        case BCH_CODE_M12:
          for (int i = 0; i < noutput_items; i += nbch) {
            //Zero the shift register
            memset(shift, 0, sizeof(unsigned int) * 6);
            // MSB of the codeword first
            for (int j = 0; j < (int)kbch; j++) {
              temp = *in++;
              *out++ = temp;
              consumed++;
              b = (temp ^ ((shift[5] & 0x00001000) ? 1 : 0));
              reg_6_shift(shift);
              if (b) {
                shift[0] ^= m_poly_m_12[0];
                shift[1] ^= m_poly_m_12[1];
                shift[2] ^= m_poly_m_12[2];
                shift[3] ^= m_poly_m_12[3];
                shift[4] ^= m_poly_m_12[4];
                shift[5] ^= m_poly_m_12[5];
              }
            }
            // Now add the parity bits to the output
            for (int n = 0; n < 180; n++) {
              *out++ = (shift[5] & 0x00001000) ? 1 : 0;
              reg_6_shift(shift);
            }
          }
          break;
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (consumed);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dtv */
} /* namespace gr */

