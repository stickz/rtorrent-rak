// rTorrent - BitTorrent client
// Copyright (C) 2005, Jari Sundell
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Contact:  Jari Sundell <jaris@ifi.uio.no>
//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#ifndef RTORRENT_CORE_DOWNLOAD_SLOT_MAP_H
#define RTORRENT_CORE_DOWNLOAD_SLOT_MAP_H

#include <map>
#include <string>
#include <sigc++/slot.h>

#include "download.h"

namespace core {

class DownloadSlotMap : public std::map<std::string, sigc::slot1<void, Download*> > {
public:
  typedef sigc::slot1<void, Download*>        SlotDownload;
  typedef std::map<std::string, SlotDownload> Base;
  
  void                insert(const std::string& key, SlotDownload s)    { Base::operator[](key) = s; }
  void                erase(const std::string& key) {}

  void                for_each(Download* d);
};

inline void
DownloadSlotMap::for_each(Download* d) {
  for (iterator itr = begin(), last = end(); itr != last; ++itr)
    itr->second(d);
}

}

#endif