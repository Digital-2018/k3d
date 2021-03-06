#ifndef MODULES_INDIGO_MATERIAL_H
#define MODULES_INDIGO_MATERIAL_H

// K-3D
// Copyright (c) 1995-2009, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
	\author Tim Shead <tshead@k-3d.com>
*/

#include <k3dsdk/imaterial.h>
#include <k3dsdk/types.h>

#include <iosfwd>

namespace module
{

namespace indigo
{

/////////////////////////////////////////////////////////////////////////////
// material

/// Used to "flag" Indigo material objects
class material :
  public k3d::imaterial
{
public:
  virtual void setup(const k3d::string_t& Name, std::ostream& Stream) = 0;
};

} // namespace indigo

} // namespace module

#endif // !MODULES_INDIGO_MATERIAL_H

