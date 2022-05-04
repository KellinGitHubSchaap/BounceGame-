#ifndef GBA_BITFIELD_H
#define GBA_BITFIELD_H

#define PREPARE_BITFIELD(value, name)		((value)& name##_MASK)																//!< Prepare a bitfield
#define	GET_BITFIELD(field, name)			((field)& name##_MASK)																//!< Get a bitfield
#define SET_BITFIELD(field, value, name)	(field = ((field)&~name##_MASK) | PREPARE_BITFIELD(value, name))					//!< Set a bitfield

#define PREPARE_SHIFTED_BITFIELD(value, name)		(((value)<<name##_SHIFT)& name##_MASK)										//!< Prepare a bitfield that uses shifting
#define GET_SHIFTED_BITFIELD(field, name)			(((field) & name##_MASK >> name##_SHIFT)									//!< get a bitfield that uses shifting
#define SET_SHIFTED_BITFIELD(field, value, name)	(field = ((field) &~name##_MASK) | PREPARE_SHIFTED_BITFIELD(value, name))	//!< Set a bitfield that uses shifting

#endif // !GBA_BITFIELD_H
