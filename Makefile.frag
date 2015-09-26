phpaci: $(BUILD_BINARY)
	
$(BUILD_BINARY): $(PHP_GLOBAL_OBJS) $(PHP_BINARY_OBJS) $(PHP_PHPACI_OBJS)
	$(BUILD_PHPACI)

install-phpaci: $(BUILD_BINARY)
	@echo "Installing PHP ACI binary: $(INSTALL_ROOT)$(bindir)"
	@$(mkinstalldirs) $(INSTALL_ROOT)$(bindir)
	@$(INSTALL) -m 0755 $(BUILD_BINARY) $(INSTALL_ROOT)$(bindir)/$(program_prefix)php$(program_suffix)$(EXEEXT)
