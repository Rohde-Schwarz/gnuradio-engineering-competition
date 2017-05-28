/* -*- c++ -*- */
/*
 * Copyright 2017 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_DTV_DVBT2_ENCODER_COMP_IMPL_H
#define INCLUDED_DTV_DVBT2_ENCODER_COMP_IMPL_H

#include <gnuradio/dtv/dvbt2_encoder_comp.h>

namespace gr {
  namespace dtv {

    class dvbt2_encoder_comp_impl : public dvbt2_encoder_comp
    {
     private:
      // Nothing to declare in this block.

     public:
      dvbt2_encoder_comp_impl(size_t fft_len);
      ~dvbt2_encoder_comp_impl();

      // Where all the action really happens
    };

  } // namespace dtv
} // namespace gr

#endif /* INCLUDED_DTV_DVBT2_ENCODER_COMP_IMPL_H */
