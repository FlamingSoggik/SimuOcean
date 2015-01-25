#ifndef CHANGERMODETERMINAL_H
#define CHANGERMODETERMINAL_H

///
/// \brief mode_raw Active ou désactive le mode raw du terminal sous linux afin que getchar() n'attende pas le retour charriot)
/// \param activer 0 : désactive le mode raw du terminal, 1: active le mode raw du terminal
///
void mode_raw(int activer);

#endif // CHANGERMODETERMINAL_H
