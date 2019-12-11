#ifndef __LOGWINDOW__
#define __LOGWINDOW__


#include "ExtraLibs/imgui/imgui.h"
#include "ExtraLibs/imgui/imgui_impl_glfw.h"
#include "ExtraLibs/imgui/imgui_impl_opengl3.h"


class LogWindow
{
public:

	// LogWindow(LogWindow const& c); // CPY CTOR
	// LogWindow(LogWindow const && c); // MV CTOR
	~LogWindow() = default; // DTOR

#pragma region public attributes
	ImGuiTextBuffer		buf;
	ImGuiTextFilter		filter;
	ImVector<int>		lineOffsets;
	bool				autoScroll;
	bool				draw;
	bool				reseted;
#pragma endregion

#pragma region public methods
	LogWindow()
	{
		autoScroll = true;
		draw = true;
		Clear();
	}

	void	Clear()
	{
		buf.clear();
		lineOffsets.clear();
		lineOffsets.push_back(0);
	}

	void ResetPos()
	{
		ImGui::SetWindowPos(ImVec2(40,40));
	}

	void	AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		int old_size = buf.size();
		va_list args;
		va_start(args, fmt);
		buf.appendfv(fmt, args);
		va_end(args);
		for (int new_size = buf.size(); old_size < new_size; old_size++)
			if (buf[old_size] == '\n')
				lineOffsets.push_back(old_size + 1);
	}

	void	Draw(const char* title, bool* p_open = NULL)
	{
		if (!draw)
			return;

		if (!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}

		if (!reseted)
		{
			ResetPos();
			reseted = true;
		}

		// Options menu
		if (ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll", &autoScroll);
			ImGui::EndPopup();
		}

		// Main window
		if (ImGui::Button("Options"))
			ImGui::OpenPopup("Options");
		ImGui::SameLine();
		bool clear = ImGui::Button("Clear");
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();
		filter.Draw("Filter", -100.0f);

		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

		if (clear)
			Clear();
		if (copy)
			ImGui::LogToClipboard();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* _buf = buf.begin();
		const char* buf_end = buf.end();
		if (filter.IsActive())
		{
			// In this example we don't use the clipper when Filter is enabled.
			// This is because we don't have a random access on the result on our filter.
			// A real application processing logs with ten of thousands of entries may want to store the result of search/filter.
			// especially if the filtering function is not trivial (e.g. reg-exp).
			for (int line_no = 0; line_no < lineOffsets.Size; line_no++)
			{
				const char* line_start = _buf + lineOffsets[line_no];
				const char* line_end = (line_no + 1 < lineOffsets.Size) ? (_buf + lineOffsets[line_no + 1] - 1) : buf_end;
				if (filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else
		{
			// The simplest and easy way to display the entire buffer:
			//   ImGui::TextUnformatted(buf_begin, buf_end);
			// And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward to skip non-visible lines.
			// Here we instead demonstrate using the clipper to only process lines that are within the visible area.
			// If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them on your side is recommended.
			// Using ImGuiListClipper requires A) random access into your data, and B) items all being the  same height,
			// both of which we can handle since we an array pointing to the beginning of each line of text.
			// When using the filter (in the block of code above) we don't have random access into the data to display anymore, which is why we don't use the clipper.
			// Storing or skimming through the search result would make it possible (and would be recommended if you want to search through tens of thousands of entries)
			ImGuiListClipper clipper;
			clipper.Begin(lineOffsets.Size);
			while (clipper.Step())
			{
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{
					const char* line_start = _buf + lineOffsets[line_no];
					const char* line_end = (line_no + 1 < lineOffsets.Size) ? (_buf + lineOffsets[line_no + 1] - 1) : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
	}
#pragma endregion
};

#endif // __LOGWINDOW__