###########################################################################
# Copyright(c) 2007 Atheros Corporation. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 59
# Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
###########################################################################

obj-m += src/

Version=1.0.1.7
ModName=alx

TAR=tar
RM=rm -fr
RPMBUILD=rpmbuild
MKDIR=mkdir
CP= cp -a
CD=cd
DKMS=dkms
SourceDir=$(ModName)-$(Version)
SourceTar=/usr/src/redhat/SOURCES/$(ModName)-$(Version).tar.gz

all:
	$(MAKE) -C ./src 

install:
	$(MAKE) -C ./src/ install

clean:
	$(MAKE) -C ./src/ clean
	$(RM) ./src/tags ./src/cscope.out ./src/cscope.*.out
rpm:
	dos2unix alx.spec
	$(MAKE) -C ./src/ clean
	$(RM) /tmp/$(SourceDir)
	$(MKDIR) /tmp/$(SourceDir)
	$(CP) ./* /tmp/$(SourceDir)
	tmppwd=`pwd`
	$(CD) /tmp/;echo `pwd`; $(TAR) -czvf $(SourceTar) $(SourceDir)
	$(CD) $(tmppwd)
	$(RPMBUILD) -ba $(ModName).spec

dkms:
	$(MAKE) -C ./src/ clean
	#$(DKMS) remove -m $(ModName) -v $(Version) --all
	$(RM) /usr/src/$(SourceDir)
	$(MKDIR) /usr/src/$(SourceDir)
	$(CP) ./* /usr/src/$(SourceDir)
	$(DKMS) add -m $(ModName) -v $(Version)
	$(DKMS) build -m $(ModName) -v $(Version)
	$(DKMS) mkdeb -m $(ModName) -v $(Version)


