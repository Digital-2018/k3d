// K-3D
// Copyright (c) 1995-2008, Timothy M. Shead
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

#include <k3dsdk/metadata_keys.h>
#include <k3dsdk/paraboloid.h>
#include <k3dsdk/primitive_validation.h>
#include <k3dsdk/selection.h>
#include <k3dsdk/string_cast.h>

namespace k3d
{

namespace paraboloid
{

/////////////////////////////////////////////////////////////////////////////////////////////
// const_primitive

const_primitive::const_primitive(
	const mesh::matrices_t& Matrices,
	const mesh::materials_t& Materials,
	const mesh::doubles_t& Radii,
	const mesh::doubles_t& ZMin,
	const mesh::doubles_t& ZMax,
	const mesh::doubles_t& SweepAngles,
	const mesh::selection_t& Selections,
	const mesh::table_t& ConstantAttributes,
	const mesh::table_t& SurfaceAttributes,
	const mesh::table_t& ParameterAttributes
		) :
	matrices(Matrices),
	materials(Materials),
	radii(Radii),
	z_min(ZMin),
	z_max(ZMax),
	sweep_angles(SweepAngles),
	selections(Selections),
	constant_attributes(ConstantAttributes),
	surface_attributes(SurfaceAttributes),
	parameter_attributes(ParameterAttributes)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
// primitive

primitive::primitive(
	mesh::matrices_t& Matrices,
	mesh::materials_t& Materials,
	mesh::doubles_t& Radii,
	mesh::doubles_t& ZMin,
	mesh::doubles_t& ZMax,
	mesh::doubles_t& SweepAngles,
	mesh::selection_t& Selections,
	mesh::table_t& ConstantAttributes,
	mesh::table_t& SurfaceAttributes,
	mesh::table_t& ParameterAttributes
		) :
	matrices(Matrices),
	materials(Materials),
	radii(Radii),
	z_min(ZMin),
	z_max(ZMax),
	sweep_angles(SweepAngles),
	selections(Selections),
	constant_attributes(ConstantAttributes),
	surface_attributes(SurfaceAttributes),
	parameter_attributes(ParameterAttributes)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
// create

primitive* create(mesh& Mesh)
{
	mesh::primitive& generic_primitive = Mesh.primitives.create("paraboloid");

	primitive* const result = new primitive(
		generic_primitive.structure["surface"].create<mesh::matrices_t >("matrices"),
		generic_primitive.structure["surface"].create<mesh::materials_t >("materials"),
		generic_primitive.structure["surface"].create<mesh::doubles_t >("radii"),
		generic_primitive.structure["surface"].create<mesh::doubles_t >("z_min"),
		generic_primitive.structure["surface"].create<mesh::doubles_t >("z_max"),
		generic_primitive.structure["surface"].create<mesh::doubles_t >("sweep_angles"),
		generic_primitive.structure["surface"].create<mesh::selection_t>("selections"),
		generic_primitive.attributes["constant"],
		generic_primitive.attributes["surface"],
		generic_primitive.attributes["parameter"]
		);

	result->selections.set_metadata_value(metadata::key::role(), metadata::value::selection_role());

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// validate

const_primitive* validate(const mesh& Mesh, const mesh::primitive& Primitive)
{
	if(Primitive.type != "paraboloid")
		return 0;

	try
	{
		require_valid_primitive(Mesh, Primitive);

		const mesh::table_t& surface_structure = require_structure(Primitive, "surface");

		const mesh::table_t& constant_attributes = require_attributes(Primitive, "constant");
		const mesh::table_t& surface_attributes = require_attributes(Primitive, "surface");
		const mesh::table_t& parameter_attributes = require_attributes(Primitive, "parameter");

		const mesh::matrices_t& matrices = require_array<mesh::matrices_t >(Primitive, surface_structure, "matrices");
		const mesh::materials_t& materials = require_array<mesh::materials_t >(Primitive, surface_structure, "materials");
		const mesh::doubles_t& radii = require_array<mesh::doubles_t >(Primitive, surface_structure, "radii");
		const mesh::doubles_t& z_min = require_array<mesh::doubles_t >(Primitive, surface_structure, "z_min");
		const mesh::doubles_t& z_max = require_array<mesh::doubles_t >(Primitive, surface_structure, "z_max");
		const mesh::doubles_t& sweep_angles = require_array<mesh::doubles_t >(Primitive, surface_structure, "sweep_angles");
		const mesh::selection_t& selections = require_array<mesh::selection_t>(Primitive, surface_structure, "selections");

		require_metadata(Primitive, selections, "selections", metadata::key::role(), metadata::value::selection_role());

		require_table_row_count(Primitive, parameter_attributes, "parameter", surface_structure.row_count() * 4);

		return new const_primitive(matrices, materials, radii, z_min, z_max, sweep_angles, selections, constant_attributes, surface_attributes, parameter_attributes);
	}
	catch(std::exception& e)
	{
		log() << error << e.what() << std::endl;
	}
	
	return 0;
}

primitive* validate(const mesh& Mesh, mesh::primitive& Primitive)
{
	if(Primitive.type != "paraboloid")
		return 0;

	try
	{
		require_valid_primitive(Mesh, Primitive);

		mesh::table_t& surface_structure = require_structure(Primitive, "surface");

		mesh::table_t& constant_attributes = require_attributes(Primitive, "constant");
		mesh::table_t& surface_attributes = require_attributes(Primitive, "surface");
		mesh::table_t& parameter_attributes = require_attributes(Primitive, "parameter");

		mesh::matrices_t& matrices = require_array<mesh::matrices_t >(Primitive, surface_structure, "matrices");
		mesh::materials_t& materials = require_array<mesh::materials_t >(Primitive, surface_structure, "materials");
		mesh::doubles_t& radii = require_array<mesh::doubles_t >(Primitive, surface_structure, "radii");
		mesh::doubles_t& z_min = require_array<mesh::doubles_t >(Primitive, surface_structure, "z_min");
		mesh::doubles_t& z_max = require_array<mesh::doubles_t >(Primitive, surface_structure, "z_max");
		mesh::doubles_t& sweep_angles = require_array<mesh::doubles_t >(Primitive, surface_structure, "sweep_angles");
		mesh::selection_t& selections = require_array<mesh::selection_t>(Primitive, surface_structure, "selections");

		require_metadata(Primitive, selections, "selections", metadata::key::role(), metadata::value::selection_role());

		require_table_row_count(Primitive, parameter_attributes, "parameter", surface_structure.row_count() * 4);

		return new primitive(matrices, materials, radii, z_min, z_max, sweep_angles, selections, constant_attributes, surface_attributes, parameter_attributes);
	}
	catch(std::exception& e)
	{
		log() << error << e.what() << std::endl;
	}
	
	return 0;
}

primitive* validate(const mesh& Mesh, pipeline_data<mesh::primitive>& Primitive)
{
  if(!Primitive.get())
    return 0;

	if(Primitive->type != "paraboloid")
		return 0;

  return validate(Mesh, Primitive.writable());
}

} // namespace paraboloid

} // namespace k3d

