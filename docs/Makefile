include version.mk.doxy

default: guide ref
all a: gh gp gt rh rm rp
usage u help h:
	@echo ""
	@echo "Targets:"
	@echo "- $(MAKE) guide      (for gmtl programmer guide: html, pdf, txt)"
	@echo "- $(MAKE) guide-html (for gmtl programmer guide: html)"
	@echo "- $(MAKE) guide-pdf  (for gmtl programmer guide: pdf)"
	@echo "- $(MAKE) guide-txt  (for gmtl programmer guide: txt)"
	@echo "- $(MAKE) man        (for man page reference)"
	@echo "- $(MAKE) ref        (for html reference manual)"
	@echo "- $(MAKE) ref-latex  (for latex reference manual)"
	@echo "- $(MAKE) ref-pdf    (for pdf reference manual)"
	@echo "- $(MAKE) clean      (remove everything that was built)"
	@echo ""

ref reference rh:
	python ex_builder.py ../examples/gmtlexamples.doxy.in 	\
           ../examples/gmtlexamples.doxy
	doxygen gmtl.doxy

ref-latex rl:
	doxygen gmtl.latex.doxy

ref-pdf rp: rl
	-mkdir pdf
	cd latex && make pdf
	cp latex/refman.pdf pdf/ref-guide.pdf

man ref-man rm manpage m:
	doxygen gmtl.man.doxy

guide g:
	-cd programmer.guide && $(MAKE)

guide-html gh:
	-cd programmer.guide && $(MAKE) html
guide-pdf gp:
	-cd programmer.guide && $(MAKE) pdf
guide-txt gt:
	-cd programmer.guide && $(MAKE) txt

# useful for creating a tree that can be tarred up and posted to a 
# website for download.
#
# prefix: Specify the dir you want the docs dumped into, can be a 
#         new dir one level deep.  Defaults to "./installed"
prefix ?=./installed
version ?=$(PROJECT_NUMBER)
install:
	-mkdir $(prefix)
	-cp -r html $(prefix)/gmtlReferenceGuide-$(version)-html
	-cp -r man $(prefix)/gmtlReferenceGuide-$(version)-man
	-cp pdf/ref-guide.pdf $(prefix)/gmtlReferenceGuide-$(version).pdf
	-cp programmer.guide/guide.pdf $(prefix)/gmtlProgrammersGuide-$(version).pdf
	-mkdir $(prefix)/gmtlProgrammersGuide-$(version)-html
	-cp programmer.guide/guide.html $(prefix)/gmtlProgrammersGuide-$(version)-html/index.html

tarballname ?=gmtldocs-$(version)
tempdirname ?=temp-gmtldoc16981418215
tarball:
	-mkdir $(tempdirname)
	$(MAKE) prefix=$(tempdirname)/$(tarballname) install
	cd $(tempdirname) && tar -zcvf $(tarballname).tgz $(tarballname) && mv $(tarballname).tgz ../ && rm $(tempdirname)

clean c:
	-rm -rf html man pdf latex installed $(tempdirname)
	rm ../examples/gmtlexamples.doxy
	-cd programmer.guide && $(MAKE) clean clobber

clobber: clean
	-rm $(tarballname).tgz
