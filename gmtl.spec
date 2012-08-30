# Spec file for GMTL.
%define name    gmtl
%define version	0.5.4
%define release	1

Name: %{name}
Summary: The GMTL Headers
Version: %{version}
Release: %{release}
Source: %{name}-%{version}.tar.gz
URL: http://ggt.sourceforge.net/
Group: Development/C++
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot
License: LGPL
BuildPrereq: scons >= 0.96.1
BuildArch: noarch
Requires: flagpoll >= 0.8.1

%description
The Generic Math Template Library (GMTL) is a high-performance, extensible,
and generic math library. The design is based upon discussion with many
experts in the field of computer graphics and virtual reality, culminating the
efforts of many previous math library efforts. GMTL gives the graphics
programmer several core math types and a rich library of graphics/math
operations on those types.

%package config
Summary: The gmtl-config script that calls flagpoll
Group: Development/C++
Requires: gmtl
Requires: flagpoll >= 0.8.1
Requires: python

%description config
The gmtl-config Python script that provides backwards compability for older
packages not using Flagpoll for getting compiler options necessary for
building against GMTL.

%package doc
Summary: GMTL API documentation
Group: Development/C++
BuildPrereq: doxygen
BuildPrereq: graphviz

%description doc
GMTL API documentation in HTML form and as man pages.

%prep
rm -rf %{buildroot}
%setup -q

%build
# This needs to be fixed once we have a boost install.
scons prefix=%{_prefix}
cd docs && make ref man
cd ..

%install
[ -z %{buildroot} ] || rm -rf %{buildroot}

scons install prefix=%{buildroot}%{_prefix}
# Remove all stupid scons temp files
find %{buildroot}%{_prefix} -name .sconsign -exec rm {} \;
find %{buildroot}%{_prefix}/include -name \*.h -exec chmod 644 {} \;
mkdir -p %{buildroot}%{_docdir}/gmtl-%{version}
mv docs/html %{buildroot}%{_docdir}/gmtl-%{version}
mv docs/man %{buildroot}%{_docdir}/gmtl-%{version}
for f in README AUTHORS ChangeLog COPYING LICENSE.addendum ; do
   cp $f %{buildroot}%{_docdir}/gmtl-%{version}
done

%clean
[ -z %{buildroot} ] || rm -rf %{buildroot}

%pre

%post

%preun

%postun

%files
%defattr(-, root, root)
%dir %{_includedir}/gmtl-%{version}/
%dir %{_includedir}/gmtl-%{version}/gmtl/
%{_includedir}/gmtl-%{version}
%{_datadir}/flagpoll
%dir %{_docdir}/gmtl-%{version}/
%doc %{_docdir}/gmtl-%{version}/AUTHORS
%doc %{_docdir}/gmtl-%{version}/ChangeLog
%doc %{_docdir}/gmtl-%{version}/COPYING
%doc %{_docdir}/gmtl-%{version}/LICENSE.addendum
%doc %{_docdir}/gmtl-%{version}/README

%files config
%{_bindir}/gmtl-config

%files doc
%dir %{_docdir}/gmtl-%{version}/
%doc %{_docdir}/gmtl-%{version}/html
%doc %{_docdir}/gmtl-%{version}/man

%changelog
* Wed Jun 27 2007 Patrick Hartling <patrick@infiscape.com> 0.5.4-1
- Updated version to 0.5.4

* Wed Jun 27 2007 Patrick Hartling <patrick@infiscape.com> 0.5.3-4
- Package documentation in HTML and man page forms.

* Wed Jun 27 2007 Patrick Hartling <patrick@infiscape.com> 0.5.3-3
- Package gmtl-config separately so that multiple versions of the gmtl
  package can be installed in parallel.

* Wed Jun 27 2007 Patrick Hartling <patrick@infiscape.com> 0.5.3-2
- The .fpc file now uses a relative path, so it is not necessary to perform
  post processing on it to remove the staging area path..

* Mon Jun 25 2007 Patrick Hartling <patrick@infiscape.com> 0.5.3-1
- Updated version to 0.5.3

* Mon Jun 25 2007 Patrick Hartling <patrick@infiscape.com> 0.5.2-1
- Updated version to 0.5.2

* Wed Jun 13 2007 Patrick Hartling <patrick@infiscape.com> 0.5.1-1
- Updated to version 0.5.1
- Fixed bad path in the GMTL .fpc file caused by the build not handling the
  staging root correctly
- Package versioned header directory

* Wed Jun 13 2007 Patrick Hartling <patrick@infiscape.com>
- Updated for the use of Flagpoll rather than pkg-config

* Wed Jan 10 2007 Patrick Hartling <patrick@infiscape.com>
- Fixed packaging errors
