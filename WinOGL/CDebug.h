#pragma once
class CDebug{
public:
	/// <summary>
	/// 引数で渡された文字をデバック時のみターミナルに出力します
	/// </summary>
	void printf_ex(LPCTSTR pszFormat, ...);
};

