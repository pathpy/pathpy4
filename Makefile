.PHONY: misc

misc:
	@echo "Hello World"

venv:
	: # Create venv if it doesn't exist
	@echo "Setup python virtual environment"
	@test -d venv || python3 -m venv venv

prepare_venv:
	@echo "Prepare virtual environment"
	@. venv/bin/activate && (\
	python -m pip install --upgrade pip setuptools wheel; \
	python -m pip install pip-tools; \
	python -m piptools sync requirements/requirements.txt requirements/dev-requirements.txt \
	)

pre_commit:
	@echo "Enable pre-commit"
	@. venv/bin/activate && pre-commit install

setup: venv prepare_venv pre_commit

clean:
	rm -rf venv
	find -iname "*.pyc" -delete
