#ifndef NOTE_MUSIC_H
#define NOTE_MUSIC_H

#include "interfaces/emun/NoteFrequency.hpp"
#include <stdint.h>

/**
 * @struct INoteMusic
 */
struct NoteMuic
{
    Note note;         // note.
    uint16_t duration; // durée de la note
};

#endif