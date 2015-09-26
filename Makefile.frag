phpaci: $(SAPI_PHPACI_PATH)

$(SAPI_PHPACI_PATH): $(PHP_GLOBAL_OBJS) $(PHP_BINARY_OBJS) $(PHP_PHPACI_OBJS)
	$(BUILD_PHPACI)

install-phpaci: $(SAPI_PHPACI_PATH)
	@echo "Installing PHP PHPACI binary:        $(INSTALL_ROOT)$(bindir)/"
	@$(mkinstalldirs) $(INSTALL_ROOT)$(bindir)
	@$(INSTALL) -m 0755 $(SAPI_PHPACI_PATH) $(INSTALL_ROOT)$(bindir)/$(program_prefix)php$(program_suffix)$(EXEEXT)

