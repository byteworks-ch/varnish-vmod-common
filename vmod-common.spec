Summary: Common VMOD for Varnish
Name: vmod-common
Version: 1.0
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
Source0: libvmod-common.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish > 3.0
BuildRequires: make, python-docutils


%description
A varnish vmod for common functions (similar to the std vmod)


%prep
%setup -n libvmod-common


%build
# this assumes that VARNISHSRC is defined on the rpmbuild command line, like this:
# rpmbuild -bb --define 'VARNISHSRC /home/user/rpmbuild/BUILD/varnish-3.0.3' redhat/*spec
./configure VARNISHSRC=%{VARNISHSRC} VMODDIR="$(PKG_CONFIG_PATH=%{VARNISHSRC} pkg-config --variable=vmoddir varnishapi)" --prefix=/usr/ --docdir='${datarootdir}/doc/%{name}'
make
make check


%install
make install DESTDIR=%{buildroot}


%clean
rm -rf %{buildroot}


%files
%defattr(-,root,root,-)
%{_libdir}/varnish/vmods/
%doc /usr/share/doc/%{name}/*
%{_mandir}/man?/*


%changelog
* Fri May 09 2014 Michael Bischof <mb@byteworks.ch> - 1.0-1
- Initial version.

