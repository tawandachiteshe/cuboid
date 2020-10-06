#if _MSVC
#pragma once
#endif

#ifndef IMGUIDOCK_H
#define IMGUIDOCK_H

namespace Cuboid
{

    void BeginDockSpace(bool *p_open);

    void EndDockSpace();

    void ShowDockingDisabledMessage();

}
#endif
